package com.example.mvcproducts.controllers;

import com.example.mvcproducts.domain.Grade;
import com.example.mvcproducts.domain.User;
import com.example.mvcproducts.repositories.UserRepository;
import com.example.mvcproducts.services.GradeService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import java.security.Principal;
import java.time.LocalDateTime;
@Slf4j
@Controller
@RequestMapping("/exercises")
public class ExercisesController {
    @Autowired
    UserDetailsService userDetailsService;

    @GetMapping
    public String exercises(Model model, Principal principal){
        model.addAttribute("isAuthenticated", true);
        UserDetails userDetails = userDetailsService.loadUserByUsername(principal.getName());
        model.addAttribute("isUser", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("USER")));
        model.addAttribute("isAdmin", userDetails.getAuthorities().stream().anyMatch(a -> a.getAuthority().equals("ADMIN")));

        return "exercises";
    }

    private final GradeService gradeService;
    @Autowired
    UserRepository userRepository;
    public ExercisesController(GradeService gradeService){
        this.gradeService=gradeService;
    }


    @PostMapping
    public String submitQuiz(Grade grade) {

        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        UserDetails userDetails = (UserDetails) authentication.getPrincipal();
        grade.setCompletionTime(LocalDateTime.now());

        User user = userRepository.findByEmail(userDetails.getUsername());

        grade.setUser(user);

        gradeService.saveGrade(grade);

        return "redirect:/user-page";
    }
}
