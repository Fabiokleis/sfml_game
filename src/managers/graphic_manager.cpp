#include "graphic_manager.hpp"
using namespace Managers;

GraphicManager::GraphicManager(const std::string& window_title) : event(), view() {
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_X,  WINDOW_Y), window_title);
    this->window->setFramerateLimit(FPS);
}

GraphicManager::~GraphicManager() {
    delete window;
}

bool GraphicManager::is_open() {
    return this->window->isOpen();
}

bool GraphicManager::poll_event() {
    return this->window->pollEvent(this->event);
}

sf::Event& GraphicManager::get_event() {
    return this->event;
}

void GraphicManager::set_view(sf::View view) {
    this->window->setView(view);
}

void GraphicManager::reset_view() {
    this->window->setView(sf::View(sf::FloatRect(0.0f, 0.0f, WINDOW_X, WINDOW_Y)));
}

void GraphicManager::clear() {
    this->window->clear();
}

void GraphicManager::close() {
    this->window->close();
}

void GraphicManager::display() {
    this->window->display();
}

void GraphicManager::render(const sf::Drawable& object) {
    this->window->draw(object);
}

sf::Vector2f GraphicManager::get_view_size() {
    return this->view.getSize();
}

void GraphicManager::resize_view(sf::Vector2f size) {
    this->view.setSize(size);
}

sf::Vector2f GraphicManager::get_window_size() {
    return sf::Vector2f(this->window->getSize());
}