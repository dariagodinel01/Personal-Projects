package com.example.mvcproducts.controllers;

import com.example.mvcproducts.domain.Form;
import com.example.mvcproducts.services.FormService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@Slf4j
@RequestMapping("/home")
public class FormController {

    private final FormService formService;

    public FormController(FormService formService) {
        this.formService = formService;
    }


    @PostMapping
    public String submitForm(Form form){
        formService.save(form);
        return "redirect:/";
    }
}