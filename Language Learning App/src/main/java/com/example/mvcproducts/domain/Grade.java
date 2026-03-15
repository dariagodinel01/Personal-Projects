package com.example.mvcproducts.domain;

import jakarta.persistence.*;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;
import java.util.Date;

@Entity
@Data
@NoArgsConstructor
public class Grade {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(fetch = FetchType.LAZY)
    private User user;
    private int quiz_id;
    private int grade;

    private LocalDateTime completionTime;

        public Grade(User user, int quiz_id,int grade,LocalDateTime completionTime) {
        this.user = user;
        this.quiz_id = quiz_id;
        this.grade = grade;
        this.completionTime = completionTime;
    }


}
