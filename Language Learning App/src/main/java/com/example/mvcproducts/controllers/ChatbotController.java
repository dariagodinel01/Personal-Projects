package com.example.mvcproducts.controllers;

import com.example.mvcproducts.services.ChatbotService;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ChatbotController {

    private final ChatbotService chatbotService;

    public ChatbotController(ChatbotService chatbotService) {
        this.chatbotService = chatbotService;
    }

    @PostMapping("/chatbot/get_response")
    public String getBotResponse(@RequestBody String userMessage) {
        return chatbotService.getBotResponse(userMessage);
    }
}
