package com.example.mvcproducts.controllers;


import com.example.mvcproducts.domain.Comment;
import com.example.mvcproducts.domain.Forum;
import com.example.mvcproducts.domain.User;
import com.example.mvcproducts.repositories.UserRepository;
import com.example.mvcproducts.services.ForumService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.ui.Model;

import java.time.LocalDateTime;
import java.util.List;

@Controller
@Slf4j
@RequestMapping("/forum")
public class ForumController {
    private final ForumService forumService;
    @Autowired
    UserRepository userRepository;
    public ForumController(ForumService forumService) {
        this.forumService = forumService;
    }



    @GetMapping()
    public String forum(Model model) {

        List<Forum> allForums = forumService.getAllForums();

        model.addAttribute("forums", allForums);
        model.addAttribute("forum", new Forum());
        return "forum";
    }


    @PostMapping()
    public String submitForum(Forum forum){
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        UserDetails userDetails = (UserDetails) authentication.getPrincipal();
        forum.setCompletionTime(LocalDateTime.now());

        User user = userRepository.findByEmail(userDetails.getUsername());
        forum.setUser(user);

        forumService.saveForum(forum);
        return "redirect:/forum";
    }


}
