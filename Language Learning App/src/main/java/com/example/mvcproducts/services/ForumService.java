package com.example.mvcproducts.services;

import com.example.mvcproducts.domain.Form;
import com.example.mvcproducts.domain.Forum;

import java.util.List;

public interface ForumService {
    List<Forum> getAllForums();
    List<Forum> getForumsByUserEmail(String email);
    void saveForum(Forum forum);
    Forum findById(Long id);
}
