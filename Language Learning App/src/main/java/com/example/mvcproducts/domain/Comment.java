package com.example.mvcproducts.domain;

import lombok.Data;
import lombok.NoArgsConstructor;

import jakarta.persistence.*;

import java.time.LocalDateTime;

@Entity
@Data
@NoArgsConstructor
public class Comment {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    @ManyToOne(fetch = FetchType.LAZY)
    private Forum forum;
    @ManyToOne(fetch = FetchType.LAZY)
    private User user;

    private String commentText;
    private LocalDateTime commentTime;


    public Comment(String commentText, Forum forum,User user,LocalDateTime commentTime) {
        this.forum=forum;
        this.commentText=commentText;
        this.user = user;
        this.commentTime=commentTime;

    }
}
