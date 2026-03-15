package com.example.mvcproducts.controllers;

import com.example.mvcproducts.services.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import java.security.Principal;

@Controller
public class HomeController {
  @Autowired
  UserDetailsService userDetailsService;

  @GetMapping("/home")
  public String home (Model model,Principal principal) {
    model.addAttribute("isAuthenticated", true);
    UserDetails userDetails = userDetailsService.loadUserByUsername(principal.getName());
    model.addAttribute("isUser", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("USER")));
    model.addAttribute("isAdmin", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("ADMIN")));

    return "home";
  }

}
