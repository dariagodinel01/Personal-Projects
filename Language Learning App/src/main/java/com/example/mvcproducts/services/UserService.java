package com.example.mvcproducts.services;

import com.example.mvcproducts.domain.User;
import com.example.mvcproducts.dto.UserDto;

public interface UserService {
  User save(UserDto userDto);
}
