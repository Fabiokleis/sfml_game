#include "window_server.hpp"
using namespace Controllers;

WindowServer::WindowServer(const std::string& window_title) : event(), view() {
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_X,  WINDOW_Y), window_title);
    this->window->setFramerateLimit(FPS);
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

sf::Event& WindowServer::get_event() {
    return this->event;
}

void WindowServer::set_view(sf::View view) {
    this->window->setView(view);
}

void WindowServer::reset_view() {
    this->window->setView(sf::View(sf::FloatRect(0.0f, 0.0f, WINDOW_X, WINDOW_Y)));
}

void WindowServer::clear() {
    this->window->clear();
}

void WindowServer::close() {
    this->window->close();
}

void WindowServer::display() {
    this->window->display();
}

void WindowServer::render(const sf::Drawable& object) {
    this->window->draw(object);
}

sf::Vector2f WindowServer::get_view_size() {
    return this->view.getSize();
}

void WindowServer::resize_view(sf::Vector2f size) {
    this->view.setSize(size);
}

sf::Vector2f WindowServer::get_window_size() {
    return sf::Vector2f(this->window->getSize());
}