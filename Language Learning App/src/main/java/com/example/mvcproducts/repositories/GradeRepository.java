package com.example.mvcproducts.repositories;

import com.example.mvcproducts.domain.Form;
import com.example.mvcproducts.domain.Grade;
import com.example.mvcproducts.domain.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface GradeRepository extends CrudRepository<Grade,Long> {
    List<Grade> findAll();
    List<Grade> findByUserId(Long userId);
    Optional<Grade> findFirstByUserIdOrderByCompletionTimeDesc(Long userId);


}