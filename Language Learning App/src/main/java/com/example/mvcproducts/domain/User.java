package com.example.mvcproducts.domain;

import jakarta.persistence.*;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@NoArgsConstructor
@Table(name = "user", uniqueConstraints = @UniqueConstraint(columnNames = "email"))
public class User  {

  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private Long id;

  private String email;
  private String password;
  private String fullname;
  private String role;



  public User(String email, String password, String role, String fullname) {
    super();
    this.email = email;
    this.password = password;
    this.role =role;
    this.fullname=fullname;
  }



}
