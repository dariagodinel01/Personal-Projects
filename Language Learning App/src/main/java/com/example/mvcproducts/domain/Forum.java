package com.example.mvcproducts.domain;

import lombok.Data;
import lombok.NoArgsConstructor;

import jakarta.persistence.*;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Entity
@Data
@NoArgsConstructor
public class Forum {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    @ManyToOne(fetch = FetchType.LAZY)
    private User user;
    private String message;
    private LocalDateTime completionTime;

    @OneToMany(mappedBy = "forum", cascade = CascadeType.ALL)
    private List<Comment> comments = new ArrayList<>();

    public Forum(User user, String commentText, String message, LocalDateTime completionTime) {
        this.message = message;
        this.completionTime = completionTime;
        this.user = user;
        LocalDateTime currentDateTime = LocalDateTime.now();
        Comment comment = new Comment(commentText, this, user,currentDateTime);
        this.comments.add(comment);
    }



}
