#include "checkers/board.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    Board board;
    int length = 800;
    sf::RenderWindow window(sf::VideoMode(length, length), "Checkers");
    int cellSize = length / 8;
    bool isMoving = false;
    bool white_turn = true;// Флаг для указания выбранной шашки
    int selected_checker_x, selected_checker_y;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Обработка щелчка левой кнопкой мыши
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

                    int clickedRow = static_cast<int>(worldPosition.y /
                                                      cellSize);  // Определяем строку клетки, на которую кликнул пользователь
                    int clickedColumn = static_cast<int>(worldPosition.x / cellSize);
                    // Обновление состояния игры на основе позиции мыши и т.д.
                    if (!isMoving) {
                        // Проверяем, нажал ли пользователь на шашку
                        if (board.is_busy(clickedColumn, clickedRow) && board.is_white(clickedColumn, clickedRow) == white_turn) {
                            selected_checker_x = clickedColumn;
                            selected_checker_y = clickedRow;
                            std::cout << selected_checker_y;
                            isMoving = true;
                        }
                    }
                    else {
                        // Проверяем, нажал ли пользователь на клетку
                        if(board.move_a_checker(selected_checker_x, selected_checker_y, clickedColumn, clickedRow)){
                            bool canMove;
                            if (!board.is_queen(clickedColumn, clickedRow)) {
                                canMove = (board.possible_move(clickedColumn, clickedRow, clickedColumn + 2, clickedRow + 2)
                                               || board.possible_move(clickedColumn, clickedRow, clickedColumn - 2, clickedRow - 2)
                                               || board.possible_move(clickedColumn, clickedRow, clickedColumn + 2, clickedRow - 2)
                                               || board.possible_move(clickedColumn, clickedRow, clickedColumn - 2, clickedRow + 2));

                            } else {
                                bool busy1 = false, busy2 = false, busy3 = false, busy4 = false;
                                for(int i = 1; i<7; i++){
                                    if(board.is_busy(clickedColumn+i, clickedRow+i)) busy1 = true;
                                    if(board.is_busy(clickedColumn+i, clickedRow-i)) busy2 = true;
                                    if(board.is_busy(clickedColumn-i, clickedRow+i)) busy3 = true;
                                    if(board.is_busy(clickedColumn-i, clickedRow-i)) busy4 = true;
                                    canMove = ((busy1 && !board.is_busy(clickedColumn+i, clickedRow+i)) ||
                                            (busy2 && !board.is_busy(clickedColumn+i, clickedRow-i)) ||
                                            (busy3 && !board.is_busy(clickedColumn-i, clickedRow+i)) ||
                                            (busy4 && !board.is_busy(clickedColumn-i, clickedRow-i)));
                                }
                            }
                            if (canMove) {
                                selected_checker_x = clickedColumn;
                                selected_checker_y = clickedRow;
                                isMoving = false;
                                white_turn = !white_turn;
                            }

                        }
                        isMoving = !isMoving;
                        white_turn = !white_turn;
                    }
                }
            }
        }
        window.clear(sf::Color::Black);

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                // Создайте и настройте sf::RectangleShape или sf::Sprite для клетки доски
                sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                cellShape.setPosition(i * cellSize, j * cellSize);

                sf::Texture cellTexture;
                if (!cellTexture.loadFromFile("pattern.png")) { std::cout << "error"; }
                cellShape.setTexture(&cellTexture);

                sf::Color customColor(150, 75, 200);
                if ((i + j) % 2 == 1) cellShape.setFillColor(customColor);
                else cellShape.setFillColor(sf::Color::White);

                window.draw(cellShape);

                sf::Texture checkerTexture;  // Создание объекта sf::Texture
                if (!checkerTexture.loadFromFile("checker.png")) {
                    std::cout << "error";
                }

                // Если клетка занята шашкой, создайте и отрисуйте sf::RectangleShape или sf::Sprite для шашки
                if (board.is_busy(i, j)) {
                    sf::Color customColor(75, 0, 130);
                    sf::CircleShape checker(0.4 * cellSize);
                    if (board.is_white(i, j)) checker.setFillColor(sf::Color::White);
                    else checker.setFillColor(customColor);// Устанавливаем цвет шашки
                    checker.setTexture(&checkerTexture);// Устанавливаем цвет обводки шашки// Устанавливаем толщину обводки шашки

// Устанавливаем позицию шашки на экране
                    checker.setPosition((i + 0.1) * cellSize,
                                        (j + 0.1) * cellSize);  // Устанавливаем координаты позиции шашки

// Отрисовываем шашку на экране
                    window.draw(checker);
                }
            }
        }
        if(board.the_end() != 0){
            sf::Text text;
            sf::Font font;
            if (!font.loadFromFile("BarlowCondensed-ExtraLight.ttf")) {
                std::cout << "error";
            }
            text.setFont(font);
            if(board.the_end() == 1) text.setString("Black won");
            else if(board.the_end() == 2) text.setString("White won");
            text.setCharacterSize(150);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            text.setPosition(0.175*length, 0.35*length);

            sf::Color customColor(186, 85, 211);

            sf::RectangleShape banner;
            banner.setSize(sf::Vector2f(0.8*length, 0.4*length));
            banner.setFillColor(customColor);
            banner.setOutlineThickness(2);
            sf::Texture bannerTexture;
            if (!bannerTexture.loadFromFile("pattern.png")) { std::cout << "error"; }
            banner.setTexture(&bannerTexture);
            banner.setOutlineColor(sf::Color::White);
            banner.setPosition(0.1*length, 0.3*length);

            window.draw(banner);
            window.draw(text);
        }




                // Обновление экрана
                window.display();
            }

    }