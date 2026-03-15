package com.example.mvcproducts.controllers;

import com.example.mvcproducts.domain.Grade;
import com.example.mvcproducts.domain.User;
import com.example.mvcproducts.dto.UserDto;
import com.example.mvcproducts.repositories.GradeRepository;
import com.example.mvcproducts.repositories.UserRepository;
import com.example.mvcproducts.services.GradeService;
import com.example.mvcproducts.services.GradeServiceImpl;
import com.example.mvcproducts.services.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

import java.security.Principal;
import java.util.List;
import java.util.Optional;

@Controller
public class UserController {
    @Autowired
    private UserService userService;
    @Autowired
    private  GradeServiceImpl gradeServiceImpl;

    @Autowired
    UserDetailsService userDetailsService;
    @Autowired
    UserRepository userRepository;
    @Autowired
    GradeRepository gradeRepository;
    @GetMapping("/signin")
    public String signup()
    {
        return "signin";
    }
    @PostMapping("/signin")
    public String saveUser(@ModelAttribute("user") UserDto userDto, Model model) {
        userService.save(userDto);
        model.addAttribute("message", "Registered Successfuly!");
        return "signin";
    }

    @GetMapping("/login")
    public String login() {
        return "login";
    }

    @GetMapping("/user-page")
    public String userPage (Model model, Principal principal, Authentication authentication) {
        UserDetails userDetails = userDetailsService.loadUserByUsername(principal.getName());
        model.addAttribute("user", userDetails);
        model.addAttribute("isAuthenticated", true);
        model.addAttribute("isUser", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("USER")));

        User user = userRepository.findByEmail(userDetails.getUsername());
        List<Grade> quizes = gradeRepository.findByUserId(user.getId());
        model.addAttribute("quizes", quizes);

        Optional<Grade> latestGrade = gradeRepository.findFirstByUserIdOrderByCompletionTimeDesc(user.getId());
        latestGrade.ifPresent(grade -> model.addAttribute("latestScore", grade.getGrade()));


        return "user-page";
    }

    @GetMapping("/admin-page")
    public String adminPage (Model model, Principal principal,Authentication authentication) {
        UserDetails userDetails = userDetailsService.loadUserByUsername(principal.getName());
        model.addAttribute("user", userDetails);
        model.addAttribute("isAuthenticated", true);
        model.addAttribute("isAdmin", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("ADMIN")));

        List<User> users = userRepository.findAll();
        model.addAttribute("users", users);
        return "admin-page";

    }



}
