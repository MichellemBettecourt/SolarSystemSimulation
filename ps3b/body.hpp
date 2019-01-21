#ifndef BODY_H
#define BODY_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Body : public sf::Drawable
{
public:
  Body(double w_size, double s) {window_size = w_size; scale = s;};
  Body(double window_size, double radius, double x_pos, double y_pos, double x_vel, double y_vel, double grams, std::string filename);
  void step(std::vector<Body>& planets, unsigned int current_planet, double delta_time);
  double get_x_coordinate() {return x_coordinate;};
  double get_y_coordinate() {return y_coordinate;};
  double get_x_velocity() {return x_velocity;};
  double get_y_velocity() {return x_velocity;};
  double get_mass() {return mass;};
  std::string get_filename() {return filename;};
  ~Body() {};
  friend std::istream& operator>>(std::istream& in, Body& arg);
private:
  double get_hypotenuse(double other_x, double other_y);
  double get_gravitational_force(double mass1, double mass2, double hypotenuse);
  double get_netforce(double hypotenuse, double gravitational_force, double this_coordinate, double other_coordinate);
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  double x_coordinate;
  double y_coordinate;
  double x_velocity;
  double y_velocity;
  std::string filename;
  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;
  double mass;
  double scale;
  double window_size;
};

#endif
