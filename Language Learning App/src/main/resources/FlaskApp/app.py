# -*- coding: utf-8 -*-

from flask import Flask, render_template, request, jsonify
import random
import json
import torch
import numpy as np
import nltk
import torch.nn as nn
import speech_recognition as sr
from nltk import word_tokenize

nltk.download('punkt')
from nltk.stem.porter import PorterStemmer
stemmer = PorterStemmer()

def tokenize(sentence, language='english'):
    return nltk.word_tokenize(sentence)


keywords_list = [
    "et", "ou", "bien", "soit", "car", "comme",  "puisque",
    "effectivement", "pareillement", "malgré", "quoique","évidemment",  "bref", "ainsi", "donc",  "finalement", "enfin",
    "si","probablement","apparemment", "d’où","d’abord", "premièrement", "après", "ensuite", "puis",
    "notamment", "aussi", "d’ailleurs", "également", "mais", "cependant", "or", "pourtant",  "néanmoins",
     "hormis", "excepté", "sauf","uniquement", "simplement", "quand", "lorsque", "depuis"
]

connector_patterns = [
    ["non", "seulement"],
    ["de", "plus"],
    ["mais", "encore"],
    ["d’un", "côté"],
    ["de", "l’autre"],
    ["afin", "que"],
    ["pour", "que"],
    ["de", "peur", "que"],
    ["en", "vue", "de"],
    ["de", "façon", "à", "ce", "que"],
    ["jusqu’à", "ce", "que"],
    ["en", "effet"],
    ["parce", "que"],
    ["étant", "donné"],
    ["vu", "que"],
    ["grâce", "à"],
    ["par", "suite", "de"],
    ["en", "raison", "de"],
    ["du", "fait", "que"],
    ["dans", "la", "mesure", "où"],
    ["de", "même", "que"],
    ["ainsi", "que"],
    ["autant", "que"],
    ["aussi", "que"],
    ["de", "la", "même", "façon", "que"],
    ["plus", "que"],
    ["moins", "que"],
    ["non", "moins", "que"],
    ["selon", "que"],
    ["comme", "si"],
    ["alors", "que"],
    ["en", "dépit", "de"],
    ["même", "si"],
    ["bien", "sûr"],
    ["bien", "que"],
    ["il", "est", "vrai", "que"],
    ["en", "conclusion"],
    ["pour", "conclure"],
    ["en", "somme"],
    ["en", "résumé"],
    ["en", "un", "mot"],
    ["en", "définitive"],
    ["par", "conséquent"],
    ["au", "cas", "où"],
    ["à", "condition", "que"],
    ["pourvu", "que"],
    ["à", "moins", "que"],
    ["en", "admettant", "que"],
    ["à", "supposer", "que"],
    ["en", "supposant", "que"],
    ["dans", "l’hypothèse", "où"],
    ["dans", "le", "cas", "où"],
    ["sans", "doute"],
    ["en", "conséquence"],
    ["c’est", "pourquoi"],
    ["de", "sorte", "que"],
    ["de", "façon", "que"],
    ["de", "manière", "que"],
    ["si", "bien", "que"],
    ["tout", "d’abord"],
    ["en", "premier", "lieu"],
    ["par", "exemple"],
    ["c’est", "ainsi", "que"],
    ["c’est", "le", "cas", "de"],
    ["entre", "autre"],
    ["en", "particulier"],
    ["du", "fait", "de"],
    ["en", "fait"],
    ["de", "même"],
    ["en", "revanche"],
    ["par", "contre"],
    ["au", "contraire"],
    ["d’un", "autre", "côté"],
    ["mis", "à", "part"],
    ["ne…", "que"],
    ["en", "dehors", "de"],
    ["avant", "que"],
    ["après", "que"],
    ["tandis", "que"],
    ["depuis", "que"],
    ["en", "même", "temps", "que"],
    ["pendant", "que"],
    ["au", "moment", "où"],
]


def tokenize_and_extract_keywords(text):
    # Tokenize the text into words
    words = word_tokenize(text, language='french')

    extracted_keywords = []
    idx = 0
    while idx < len(words):
        # Check if the current word and the following words match any pattern
        for pattern in connector_patterns:
            if words[idx:idx + len(pattern)] == pattern:
                temp_list = [' '.join(pattern)]
                extracted_keywords.extend(temp_list)  # Add the matched pattern to keywords
                idx += len(pattern)  # Move the index forward
                print(temp_list)
                print(pattern)
                print(extracted_keywords)
                break
        else:
            # If no match, consider the current word individually
            word = words[idx]
            if word in keywords_list:
                extracted_keywords.append(word)
            idx += 1

    print(extracted_keywords)
    return extracted_keywords

def stem(word):
    return stemmer.stem(word.lower())


def bag_of_words(tokenized_sentence, words):
    sentence_words = [stem(word) for word in tokenized_sentence]
    # initialize bag with 0 for each word
    bag = np.zeros(len(words), dtype=np.float32)
    for idx, w in enumerate(words):
        if w in sentence_words:
            bag[idx] = 1

    return bag


class NeuralNet(nn.Module):
    def __init__(self, input_size, hidden_size, num_classes):
        super(NeuralNet, self).__init__()
        self.l1 = nn.Linear(input_size, hidden_size)
        self.l2 = nn.Linear(hidden_size, hidden_size)
        self.l3 = nn.Linear(hidden_size, num_classes)
        self.relu = nn.ReLU()

    def forward(self, x):
        out = self.l1(x)
        out = self.relu(out)
        out = self.l2(out)
        out = self.relu(out)
        out = self.l3(out)

        return out


app = Flask(__name__)

# Load intents and initialize the model
with open('intents.json', 'r', encoding='utf-8') as json_data:
    intents = json.load(json_data)


device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

FILE = "data.pth"
data = torch.load(FILE)

input_size = data["input_size"]
hidden_size = data["hidden_size"]
output_size = data["output_size"]
all_words = data['all_words']
tags = data['tags']
model_state = data["model_state"]
word_translations = data["word_translations"]

model = NeuralNet(input_size, hidden_size, output_size).to(device)
model.load_state_dict(model_state)
model.eval()

chat_name = "Chat"

def get_response(sentence):
    sentence = tokenize(sentence, language='french')
    X = bag_of_words(sentence, all_words)
    X = X.reshape(1, X.shape[0])
    X = torch.from_numpy(X).to(device)

    output = model(X)
    _, predicted = torch.max(output, dim=1)

    tag = tags[predicted.item()]

    probs = torch.softmax(output, dim=1)
    prob = probs[0][predicted.item()]
    if prob.item() > 0.75:
        for intent in intents['intents']:
            if tag == intent["tag"]:
                return random.choice(intent['responses'])
    else:
        translate_keywords = ["Translate", "translation", "Translation", "translate"]
        if any(keyword in sentence for keyword in translate_keywords):
            words = [word for word in sentence if word in word_translations]
            if words:
                translations = [word_translations[word] for word in words]
                return ", ".join(translations)
            else:
                return "No translations found for the provided words."
        else:
            return "I do not understand..."


def get_response_speech(transcript):
    # Tokenize the transcript into words and expressions
    transcript_tokens = tokenize_and_extract_keywords(transcript)
    print("2")
    print(transcript_tokens)
    # Find matched keywords between transcript and predefined keywords
    matched_keywords = [token for token in transcript_tokens]
    print("3")
    print(matched_keywords)
    if matched_keywords:
        # Get bot response based on the matched keywords
        bot_response = "The logic connectors used by you are: " + ", ".join(matched_keywords)
    else:
        bot_response = "You used no logic connectors."

    print("4")
    print(bot_response)
    return bot_response

@app.route("/")
def home():
    return render_template("chatbot.html", chat_name=chat_name)


@app.route("/get_response", methods=["POST"])
def get_bot_response():
    user_message = request.form["user_message"]
    bot_response = get_response(user_message)
    return {"bot_response": bot_response, "chat_name": chat_name}


@app.route("/speech_to_text", methods=["POST"])
def speech_to_text():
    if 'user_message' in request.form:
        transcript = request.form['user_message']
        bot_response = get_response_speech(transcript)
        response_data = {"bot_response": bot_response}
        return jsonify(response_data)
    else:
        return jsonify({"error": "Invalid request, 'user_message' not found."})

if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')
