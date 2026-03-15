package com.example.mvcproducts.repositories;

import com.example.mvcproducts.domain.Comment;
import com.example.mvcproducts.domain.Form;
import com.example.mvcproducts.domain.Forum;
import com.example.mvcproducts.domain.Grade;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface CommentRepository extends CrudRepository<Comment,Long> {

}
