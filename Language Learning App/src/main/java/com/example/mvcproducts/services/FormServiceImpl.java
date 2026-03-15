package com.example.mvcproducts.services;

import com.example.mvcproducts.domain.Form;
import com.example.mvcproducts.repositories.FormRepository;
import org.springframework.stereotype.Service;

@Service
public class FormServiceImpl implements FormService {
    private final FormRepository formRepository;

    public FormServiceImpl(FormRepository formRepository) {

        this.formRepository = formRepository;
    }

    @Override
    public void save(Form form) {

        formRepository.save(form);
    }

}
