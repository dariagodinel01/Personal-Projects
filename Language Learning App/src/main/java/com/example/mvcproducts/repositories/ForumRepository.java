package com.example.mvcproducts.repositories;

import com.example.mvcproducts.domain.Form;
import com.example.mvcproducts.domain.Forum;
import com.example.mvcproducts.domain.Grade;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface ForumRepository extends CrudRepository<Forum,Long> {
    List<Forum> findAll();
    List<Forum> findByUserEmail(String email);
}
