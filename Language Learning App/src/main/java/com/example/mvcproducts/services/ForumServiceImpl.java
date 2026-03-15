package com.example.mvcproducts.services;

import com.example.mvcproducts.domain.Form;
import com.example.mvcproducts.domain.Forum;
import com.example.mvcproducts.repositories.FormRepository;
import com.example.mvcproducts.repositories.ForumRepository;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Service
public class ForumServiceImpl implements ForumService {
    private final ForumRepository forumRepository;

    public ForumServiceImpl(ForumRepository forumRepository) {

        this.forumRepository = forumRepository;
    }

    @Override
    public void saveForum(Forum forum) {
        forumRepository.save(forum);
    }

    @Override
    public List<Forum> getAllForums() {
        Iterable<Forum> forumIterable = forumRepository.findAll();
        List<Forum> forums = StreamSupport.stream(forumIterable.spliterator(), false)
                .collect(Collectors.toList());

        // Sort the forums list in descending order based on completionTime
        Comparator<Forum> byCompletionTimeDesc = Comparator.comparing(Forum::getCompletionTime).reversed();
        Collections.sort(forums, byCompletionTimeDesc);

        return forums;
    }
    @Override
    public List<Forum> getForumsByUserEmail(String email) {
        List<Forum> forums = forumRepository.findByUserEmail(email);

        Comparator<Forum> byCompletionTimeDesc = Comparator.comparing(Forum::getCompletionTime).reversed();
        forums.sort(byCompletionTimeDesc);

        return forums;
    }
    @Override
    public Forum findById(Long id) {
        Optional<Forum> optionalForum = forumRepository.findById(id);
        return optionalForum.orElse(null);
    }
}
