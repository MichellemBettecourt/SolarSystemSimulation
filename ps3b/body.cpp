#include <vector>
#include <math.h>
#include "body.hpp"

const double GRAVITATIONAL_CONSTANT = 6.67 * pow(10.0, -11.0);

double Body::get_hypotenuse(double other_x, double other_y)
{
  double hypotenuse = sqrt(pow(x_coordinate-other_x,2)+pow(y_coordinate-other_y, 2));

  return hypotenuse;
}

double Body::get_gravitational_force(double mass1, double mass2, double hypotenuse)
{
  double force = (GRAVITATIONAL_CONSTANT * (mass1 * mass2))/pow(hypotenuse, 2);

  return force;
}

double Body::get_netforce(double hypotenuse, double gravitational_force, double this_coordinate, double other_coordinate)
{
  double netforce = gravitational_force*((this_coordinate-other_coordinate)/hypotenuse);

  return netforce;
}

Body::Body(double w_size, double s, double x_pos, double y_pos, double x_vel, double y_vel, double grams, std::string image_name)
{
  x_coordinate = x_pos;
  y_coordinate = y_pos;
  x_velocity = x_vel;
  y_velocity = y_vel;
  mass = grams;
  filename = image_name;
  scale = s;
  window_size = w_size;

  if (!image.loadFromFile(filename))
  {
    std::cout << "Failed to read file." << std::endl;
  }
  if (!texture.loadFromImage(image))
  {
    std::cout << "Failed to read file." << std::endl;
  }
  sprite.setTexture(texture);
}

std::istream& operator>>(std::istream& in, Body& arg)
{
  in >> arg.x_coordinate >> arg.y_coordinate >> arg.x_velocity >> arg.y_velocity >> arg.mass >> arg.filename;
  if (!arg.image.loadFromFile(arg.filename))
  {
    std::cout << "Failed to read file." << std::endl;
  }
  if (!arg.texture.loadFromImage(arg.image))
  {
     std::cout << "Failed to read file." << std::endl;
  }
  arg.sprite.setTexture(arg.texture);
  return in;
}

void Body::step(std::vector<Body>& planets, unsigned int current_planet, double delta_time)
{
  //Update planet
  unsigned int i = 0;
  while (i < planets.size())
  {
    //current planet is what we're trying to update, no need to
    //have the same iteration number as it to modify itself
    if (current_planet != i)
    {
      double hypotenuse =
        get_hypotenuse((planets[i]).get_x_coordinate(), (planets[i]).get_y_coordinate());
      double gravitational_force = get_gravitational_force(planets[i].get_mass(), mass, hypotenuse);

      double netforce_x = get_netforce(hypotenuse, gravitational_force, x_coordinate, planets[i].get_x_coordinate());
      double netforce_y = get_netforce(hypotenuse, gravitational_force, y_coordinate, planets[i].get_y_coordinate());

      x_velocity += (delta_time*netforce_x)/mass;
      y_velocity += (delta_time*netforce_y)/mass;
    }
    i++;
  }
  x_coordinate -= (delta_time*x_velocity);
  y_coordinate -= (delta_time*y_velocity);

  //We call this to update all the other planets after updating the first planet
  if (current_planet < planets.size())
  {
    (planets[current_planet+1]).step(planets, current_planet+1, delta_time);
  }
}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  sf::Sprite temp_sprite(texture);
  double half_window_size = window_size/2;
  double half_image_size_x = image.getSize().x/2;
  double half_image_size_y = image.getSize().y/2;
  double scaled_x = x_coordinate/scale;
  double scaled_y = y_coordinate/scale;

  int temp_x = half_window_size-half_image_size_x+(scaled_x*half_window_size);
  int temp_y = half_window_size-half_image_size_y+(scaled_y*half_window_size);

  temp_sprite.setPosition(temp_x, temp_y);
  target.draw(temp_sprite, states);
}
