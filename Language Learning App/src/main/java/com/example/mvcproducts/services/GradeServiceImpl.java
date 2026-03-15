package com.example.mvcproducts.services;

import com.example.mvcproducts.domain.Grade;
import com.example.mvcproducts.domain.User;
import com.example.mvcproducts.repositories.GradeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import java.util.Date;
import java.util.Optional;

@Service

public class GradeServiceImpl implements GradeService{

    private final GradeRepository gradeRepository;

    public GradeServiceImpl(GradeRepository gradeRepository) {
        this.gradeRepository = gradeRepository;
    }
    @Override
    public void saveGrade(Grade grade) {

        gradeRepository.save(grade);
    }



}
