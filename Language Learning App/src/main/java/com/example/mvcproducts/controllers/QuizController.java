package com.example.mvcproducts.controllers;

import com.example.mvcproducts.domain.Grade;
import com.example.mvcproducts.domain.User;
import com.example.mvcproducts.repositories.UserRepository;
import com.example.mvcproducts.services.GradeService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import org.springframework.security.core.Authentication;

import java.time.LocalDateTime;

@Slf4j
@Controller
@RequestMapping("/quiz")
public class QuizController {

    private final GradeService gradeService;
    @Autowired
    UserRepository userRepository;
    public QuizController(GradeService gradeService){
        this.gradeService=gradeService;
    }

    @GetMapping
    public String quiz(){
        return "quiz";
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