<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="css/styleplay.css">
    <link rel="stylesheet" href="css/bootstrap.css">
    <title>Play</title>
</head>
<body >
   <audio id="ms" src="sound/ofeliasdream.mp3" autoplay loop></audio>
    <script>
        function readCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}
        let music=document.getElementById('ms');
        let vol=readCookie('volume');
         music.volume=vol;
</script>
   <div class="container">
  <h3 class="prompt">
    </h3>
    <h4>What do you do?</h4>
  <select class="chooser"></select>
  <button class="act-btn">Choose</button>
</div>
    <script>
        const gameConfig = [
  {
    choice: "Start Your Story",
    prompt: "Are ghosts as terrifyng as they may seem? We like to think not... Humans will fight, hurt and kill over, and over, and over again... Yet you call us worse than them? Would you like to hear our side of story before you decide which part to take?",
    options: ["Accept the proposal", "Decline"]
  },
  {
    choice: "Decline",
    prompt: "So you decided to ignore the truth? Then go on with your boring life full of prejudice! But if you ever decide that it is time for a change, we will be here to enlighten you.",
    options: ["Start Your Story", "Go to HOME Page"]
  },
  {
    choice: "Accept the proposal",
    prompt: "So you accepted...Good! Come, sit down. What I'm about to tell you, is more terrifying than any ghost. It is a tale... of humans. Think of all the terrifying stories you can swear you've heard before...Do you think they could have come from ghosts?",
    options: ["Story number 1", "Story number 2"]
  },
 {
    choice: "Story number 1",
    prompt: "As you start to listen to the story the realization hits you: ~Is this a dream? Where am I and who are these people?~ All you can remember is the long dark alley from your neighborhood. After a long day of work, you were about to go home, but now you are in an unknown place.",
    options: ["Ask the people", "Listen silently to their story"]
  },
            {
    choice: "Ask the people",
    prompt: "You gather some courage and speak: ~I'm sorry to interrupt, but can you tell where I am and how I got here?~ Suddenly everybody is looking at you and starts laughing...~Oh my, don't you remember? You, little one, are a lost soul and we are here to guide you. You can stay with us forever or you can go back to your petty humans. In the end, it is your choice.",
    options: ["Say you will listen to the story", "Ask about them"]
  },
            {
    choice: "Say you will listen to the story",
    prompt: "~Good then~ says one of them ~ My story starts long ago, so long that no book has any record of it. It all starts at a monastery where orphans are taken care of...~ As the story starts, your vision gets more and more blurry. When you open your eyes, the dark room is replaced by a simple looking room. Realizing you are in a bed, you try to get up and look in a mirror. You are no longer you as the body you posses is that of a nun.",
    options: ["Speak loud", "Get out of the room"]
  },
     {
    choice: "Speak loud",
    prompt: "In hope of being heard by the so called ghosts you ask loudly: ~Where am I? Why am I in a different body?~ After a short silence you hear a voice:~ You are in my story, but be careful: This is a place of God, so you shell never reveal your identity as there will be consequences! Now... I placed you in there so you will understend it better. From now on you are on your own. We will see you at the end... or maybe not.~ You decide to get out of your room and see what this story is about!",
    options: ["Go on", "Go on"]
  },
            {
    choice: "Go on",
    prompt: "As you leave the room, a serious looking nun is waiting near the door: ~Good morning, my dear! Now that you are awake, I have to explain some things as you are new here.~ She takes you to a small room and after putting a cup of tea on the table, she starts to speak: ~As I think you know, most of the children here are sick. Even though we've gotten some recent exposure due to our eccentric priest, there's a limit to how much donations that can bring. It's a struggle to keep the orphanage open. There just isn't enough for the children's medical care...~ You listen silently while looking through a photo book of the children.",
    options: ["Go to see the priest", "Go to see the children"]
  },
               {
    choice: "Go to see the priest",
    prompt: "Listening to the old nun's words, you realize that only by learning about this world, you will be able to go home: ~I would like to see the priest~ as you say that, the nun's eyes darkened. Even so, she gets up and you follow her into a small room. In there is a bed and a frail looking child with his eyes closed. By his side you see the priest praying. You learn from them that the child is greavily ill. ",
    options: ["Stay to nurse the child", "Go to see the children"]
  },
               {
    choice: "Stay to nurse the child",
    prompt: "Hearing about the child made you worry about his life so you decided to remain by his side. After a while, the priest comes back with a bowl of porridge for the child, but he refuses to eat and so the days pass by without anyone being able to help him... ~Another poor child...~ says the old nun. You look around and see everyone crying, but a young boy with dark hair who silently watches from afar.",
    options: ["Talk to him", "Ask another nun about him"]
  },
               {
    choice: "Talk to him",
    prompt: "As you try to approach him, the little boy runs away. ~Leave him~, says the priest, ~He may be suffering more than all of us as the late child was his friend.~ You decide to listen to him and help the other nuns prepare the dining room.  There you see the dark haired boy. Again he is the only one not eating. When another nun tries to make him eat, he runs away.",
    options: ["Stay silent", "Go after him"]
  },
               {
    choice: "Stay silent",
    prompt: "You decide to stay silent and ignore everything that happens, so every day brings another loss. In the end, even you fall ill and die. As you open your eyes you are back in the dark room filled with odd looking people. ~So you are no diffrent from them. I can say I had some expectations from you, but in the end all humans are either bad or ignorant.~ You try to say something, but darkness fills your senses...",
    options: ["Start Your Story", "Go to HOME Page"]
  },
             {
    choice: "Go after him",
    prompt: "In the end, you decide to go after him. In the corner, near the door you see him sitting alone. Without saying anything, you just sit close to him while putting the tray with the food down. ~Are you sure you are not hungry? Here, take a bite.~ Seeing how the boy ignores your words, you take a bite yourself to show him how good it is. Suddenly the boy tosses your spoon away while looking scared: ~ Did you eat the porridge too, sister? Then... does the sister gotta lay down now too? All my friends who eat the poridge go lay down...~",
    options: ["Run to the kitchen", "Go to the priest"]
  },
             {
    choice: "Run to the kitchen",
    prompt: "You ran to the kitchen to see the rest of the food, but nothing seems wrong with it. Then you ask on of the other nuns: ~Who brings the food to the sick children?~ As she looks taken aback by your question, she answers: ~Why... It's our father John, of course.~",
    options: ["Go to the priest", "Go to the old nun"]
  },
             {
    choice: "Go to the priest",
    prompt: "Having more questions than answers, you decide to talk to the priest. Arriving to his room, you see the door wide open. As you enter and look around for father John, you see a small bottle with a weird looking liquid. It is poison... But why whould the priest need something like this? Is he the one who makes the children so sick? ~What are you doing here?~ As you turn around, you can see the priest by the door.",
    options: ["Tell him what you found out", "Pretend"]
  },
            
             {
    choice: "Tell him what you found out",
    prompt: "~You tried to kill the sick children! But why? What is wrong with you?~ The priest smiles: ~There were many people who came to donate because of how unfortunate the children were. However, it's still not enough to take care of all of them. When they get sick, this is the only way for them to not suffer anymore~ Hearing his words, you decide to do something.",
    options: ["Run to the police", "Pretend"]
  },
             {
    choice: "Run to the police",
    prompt: "Still having the bottle in your hand, you decide to run and tell the police. However, the priests tries to stop you so you just run and run as fast as you can. ~Please wait for me children. I'll save you as soon as I can.~ you tell yourself while going down the stairs, but a moment of distraction was enough for father John to push you down the stairs. ~Is this the end? If only I could have saved the poor children...~ You ask yourself while looking at the sky unable to move. Suddenly you hear a familiar voice: ~No, my dear lost soul, this is not the end. Even though you could not save them, you showed yourself worthy of another chance. Now is your time to choose: ~",
    options: ["Go back to your life", "Remain with the ghosts"]
  },
             {
    choice: "Go back to your life",
    prompt: "~So you still decided to go back, huh? Well maybe it is not a really bad choice. I hope you learned something and from now on, you are no longer ignorant to the hardships of the world. Good luck, human!~",
    options: ["Start Your Story", "Go to HOME Page"]
  },
             {
    choice: "Remain with the ghosts",
    prompt: "Good choice, good choice. You will live forever so what can go wrong from now on, right? We will have a lot of fun together!",
    options: ["Start Your Story", "Go to HOME Page"]
  },
            {
    choice: "Pretend",
    prompt: "Even though you are taken aback, you decide that the best thing to do is pretend. You try to get out the room while taking the small bottle. ~I'm sorry, father John. I will show myself out.~ As you try to get out, the priest grabs your hand: ~Where do you think you are going now that you know my secret? Little one, I can't have you destroying my plans and my life.~ Suddenly, you feel an intense pain in your stomach. As you look down, you can see that the priest stabbed you: ~Why...?~ you try to say before falling down. Your eyes are closing slowly, the last things you see are the dark eyes and the crazy smile of father John...",
    options: ["Start Your Story", "Go to HOME Page"]
  },
            {
    choice: "Go to the old nun",
    prompt: "Going directly to the priest seems dangerous, so you decide to go to the old nun who you met the first day. As you try to explain to her your theory that the priest is trying to harm the children, the nun is listening to you silently without showing any emotion. ~I think we need to do something. We should go the police or try to investigate.~ you say hoping that the nun will be your ally. ~My dear, the truth is I also had my suspicions. If even you, who just came here, thinks the same, I think we should do something.~... After a while, together with the old nun, you gather enough information to put the priest in the prison and save the children. One day you hear the ghost's voice again: ~Congratulations! It seems you are no ordinary human. You win so you get to choose:~",
    options: ["Remain at the orphanage", "Go back to your life","Remain with the ghosts"]
  },
            {
    choice: "Remain at the orphanage",
    prompt: "After all the hardships you passed to help the poor children, you decide to stay together with them until the end. Someone has to protect their smiles, so why not you?",
    options: ["Start Your Story", "Go to HOME Page"]
  },
            {
    choice: "Ask another nun about him",
    prompt: "~I'm sorry, but who is that child? Is he ok?~ you ask the closest nun, ~Oh him? That boy is always making trouble, he never eats what we give him and is always seen alone. Still poor him, he has been alone for a long time...~",
    options: ["Go after him", "Stay silent"]
  },
              {
    choice: "Go to see the children",
    prompt: "Looking around you start to realize how weird and sad this place is. You go in the backyard to see the children. ~Gather here kids! This one here is a new member of our family so you should listen to her.~ says the old nun. You take a moment to watch each and every one of them. All of them looked like normal kids, but one who was sitting alone. A dark haired boy... Next day, at the  dining table you see again the young boy running away.",
    options: ["Go after him", "Stay silent"]
  },
          {
    choice: "Get out of the room",
    prompt: "You get scared and run out of the room. There you see a nun and start to tell her all the things that had happened to you, from walking on a the dark alley to get home to the ghosts that made you go inside the nun's body. As the nun listens to you with a terrified expresion, she starts to scream for the other nuns: ~She is possessed, she is possessed!~ From that moment, every day became a torment as more and more priests come and try to exorcise the ~ghost~ out of the nun...",
    options: ["Start Your Story", "Go to HOME Page"]
  },
          {
    choice: "Ask about them",
    prompt: "~You are here to guide me? What do you mean? Who are you?~you ask and one of them speaks loudly: ~Listen petty soul, we are the spirits that guide lost souls just like yours. You know, when a soul is too tired and sad, it loses its meaning in life. This is when we interfere and try to help you based on your worth. So that being said, you better sit down and listen to our story.~",
    options: ["Say you will listen to the story"]
  },
          {
    choice: "Listen silently to their story",
    prompt: "~My story starts long ago, so long that no book has any record of it. It all starts at a monastery where orphans are taken care of...~ As the story starts, your vision gets more and more blurry. When you open your eyes, the dark room is replaced by a simple looking room. Realizing you are in a bed, you try to get up and look in a mirror. You are no longer you as the body you posses is that of a nun.",
    options: ["Speak loud", "Get out of the room"]
  },
        
            {
    choice: "Story number 2",
    prompt: "~My story happens in a far away land, so far that no one can go there anymore. In that land, you can find the happiest people on the Earth. So happy, so talented, so smart and inventive, so creative and so free of any worries and you, my dear lost soul, can be part of that land. The only thing you have to know is that, the people's happiness is not given for free. To have something, you have to give something, and that thing is the happines of a child. You can be happy, but that child is going to suffer in the most horrid ways.~",
    options: ["Leave", "Take his place", "Be happy"]
  },
                {
    choice: "Leave",
    prompt: "~So you choose to leave and stay ignorant about his suffering...But in the end, what could you do, a mere human...~",
    options: ["Start Your Story", "Go to HOME Page"]
  },
                {
    choice: "Take his place",
    prompt: "~Oh, such a noble soul! Choosing to sacrifice yourself for the good of others. I am impressed, but is this really the right choice? Will this really solve the problem?",
    options: ["Start Your Story", "Go to HOME Page"]
  },
                {
    choice: "Be happy",
    prompt: "~Being happy... well don't we all want that? In the end, it is your choice so go on, be happy! Just try not to think about the poor child too much or your soul will rot and we will meet again...HAHAHA~",
    options: ["Start Your Story", "Go to HOME Page"]
  },
            
            
             {
    choice: "Go to HOME Page",
    
  }
            
            
];
const prompt = document.querySelector(".prompt");
const chooser = document.querySelector(".chooser");
const actBtn = document.querySelector(".act-btn");

function act(choice) {
    if(choice==="Go to HOME Page"){
        window.location.replace("Index.php");
    }
  prompt.textContent = gameConfig.filter(
    config => config.choice === choice
  )[0].prompt;
  chooser.innerHTML = gameConfig
    .find(config => config.choice === choice)
    .options.map(option => `<option value="${option}">${option}</option>`)
    .join("");
    switch(choice){
        case "Start Your Story": document.body.style.background = "url('images/candle.jpg')";
                                document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Decline": document.body.style.background = "url('images/decline.jpg')";
                                 document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Accept the proposal": document.body.style.background = "url('images/darkroom.jpg')";
                                 document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Story number 2": document.body.style.background = "url('images/story2.jpg')";
                         document.body.style.backgroundSize ="cover";
                         document.body.style.backgroundAttachment ="fixed";
                        document.body.style.backgroundPosition ="center center";
                        document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Leave": document.body.style.background = "url('images/leave.jpg')";
                                     document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Take his place": document.body.style.background = "url('images/takehisplace.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Be happy": document.body.style.background = "url('images/behappy.jpg')";
                                    document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Story number 1": document.body.style.background = "url('images/story1.jpg')";
                                        document.body.style.backgroundSize ="cover";
                                        document.body.style.backgroundAttachment ="fixed";
                                        document.body.style.backgroundPosition ="center center";
                                        document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Ask the people": document.body.style.background = "url('images/Askthepeople.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Say you will listen to the story": document.body.style.background = "url('images/saylisten.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Speak loud": document.body.style.background = "url('images/Speakloud.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Go on": document.body.style.background = "url('images/goon.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Go to see the priest": document.body.style.background = "url('images/Goseepriest.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Stay to nurse the child": document.body.style.background = "url('images/child.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Talk with him": document.body.style.background = "url('images/Talkwithhim.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Stay silent": document.body.style.background = "url('images/Staysilent.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Go after him": document.body.style.background = "url('images/Goafterhim.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Run to the kitchen": document.body.style.background = "url('images/Run.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Go to the priest": document.body.style.background = "url('images/poison.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Tell him what you found out": document.body.style.background = "url('images/tellhim.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Run to the police": document.body.style.background = "url('images/Runpolice.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Go back to your life": document.body.style.background = "url('images/Goback.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Remain with the ghosts": document.body.style.background = "url('images/Remainghosts.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Pretend": document.body.style.background = "url('images/blood.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Go to the old nun": document.body.style.background = "url('images/prison.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Remain at the orphanage": document.body.style.background = "url('images/Remainorphanage.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Ask another nun about him": document.body.style.background = "url('images/ask.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Go to see the children": document.body.style.background = "url('images/Gochildren.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Get out of the room": document.body.style.background = "url('images/cross.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
        case "Ask about them": document.body.style.background = "url('images/Askaboutthem.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         case "Listen silently to their story": document.body.style.background = "url('images/saylisten.jpg')";
                         document.body.style.backgroundSize ="cover";
                                document.body.style.backgroundAttachment ="fixed";
                                document.body.style.backgroundPosition ="center center";
                                document.body.style.backgroundRepeat ="no-repeat";
            break;
         

        }
    }
      
actBtn.addEventListener("click", () => act(chooser.value));

act("Start Your Story");
        
       
    </script>
</body>
</html>