package com.example.mvcproducts.services;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

@Service
public class ChatbotService {

    private final RestTemplate restTemplate;
    private final String chatbotServerUrl;

    public ChatbotService(RestTemplate restTemplate, @Value("${chatbot.server.url}") String chatbotServerUrl) {
        this.restTemplate = restTemplate;
        this.chatbotServerUrl = chatbotServerUrl;
    }

    public String getBotResponse(String userMessage) {
        // interact with the chatbot server using the  URL
        String botResponse = restTemplate.postForObject(chatbotServerUrl, userMessage, String.class);
        return botResponse;
    }
}
