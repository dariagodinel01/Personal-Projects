package com.example.mvcproducts.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import java.security.Principal;

@Controller
@RequestMapping("/textslvl3")
public class Textslvl3Controller {

    @Autowired
    UserDetailsService userDetailsService;

    @GetMapping
    public String textslvl3(Model model, Principal principal){
        model.addAttribute("isAuthenticated", true);
        UserDetails userDetails = userDetailsService.loadUserByUsername(principal.getName());
        model.addAttribute("isUser", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("USER")));
        model.addAttribute("isAdmin", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("ADMIN")));

        return "textslvl3";
    }
}
