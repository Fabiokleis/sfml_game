#include "window_server.hpp"
using namespace Controllers;

WindowServer::WindowServer(const std::string& window_title) {
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_X,  WINDOW_Y), window_title);
    this->window->setFramerateLimit(FPS);
    this->view = sf::View (sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
}

WindowServer::~WindowServer() {
    delete window;
}

bool WindowServer::is_open() {
    return this->window->isOpen();
}

bool WindowServer::poll_event() {
    return this->window->pollEvent(this->event);
}

sf::RenderWindow* WindowServer::get_window() {
    return this->window;
}

sf::Event& WindowServer::get_event() {
    return this->event;
}

Entities::Player* WindowServer::create_player(
        sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord,
        sf::Vector2u image_count, float switch_time, Entities::State state, const std::string &path_name)
{
    return new Entities::Player{size, velocity, position, cord, image_count, switch_time, state, path_name};
}

Maps::Map* WindowServer::create_map() {
    return new Maps::Map{};
}

Entities::Text* WindowServer::create_text(const std::string& path_name, unsigned int size, float x, float y, sf::Color color) {
    return new Entities::Text{path_name, size, x, y, color};
}

Entities::Image *WindowServer::create_image(const std::string &path_name) {
    return new Entities::Image{path_name};
}

void WindowServer::set_view() {
    this->window->setView(this->view);
}

void WindowServer::set_view_center(const sf::Vector2f position) {
    this->view.setCenter(position);
}

void WindowServer::move_view(sf::Vector2f dir) {
    this->view.move(dir);
}

void WindowServer::clear() {
    this->window->clear();
}

void WindowServer::render(const sf::Drawable& object) {
    this->window->draw(object);
}

float WindowServer::get_view_size() {
    return this->view.getSize().y;
}
