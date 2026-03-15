package com.example.mvcproducts.controllers;

import com.example.mvcproducts.domain.Comment;
import com.example.mvcproducts.domain.Forum;
import com.example.mvcproducts.domain.User;
import com.example.mvcproducts.repositories.UserRepository;
import com.example.mvcproducts.services.CommentService;
import com.example.mvcproducts.services.ForumService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.time.LocalDateTime;
@Controller
@Slf4j
@RequestMapping("/forum/comment")
public class CommentController {

    private final CommentService commentService;
    private final ForumService forumService;
    @Autowired
    UserRepository userRepository;
    @Autowired
    public CommentController(CommentService commentService, ForumService forumService) {
        this.commentService = commentService;
        this.forumService = forumService;
    }
    @PostMapping
    public String addComment(Long forumId, String commentText, Model model) {
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        UserDetails userDetails = (UserDetails) authentication.getPrincipal();
        User user = userRepository.findByEmail(userDetails.getUsername());

        Forum forum = forumService.findById(forumId);
        Comment comment = new Comment(commentText, forum, user, LocalDateTime.now());
        commentService.saveComment(comment);

        return "redirect:/forum";
    }

}
