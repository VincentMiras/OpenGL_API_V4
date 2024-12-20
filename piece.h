#ifndef PIECE_H
#define PIECE_H

#include"glm/glm.hpp"
#include "Piececolor.h"
#include <vector>

class Piece
{
public:
    Piece(PieceColor color, glm::vec2 pos);
    virtual ~Piece();
    virtual std::vector<glm::vec2> MouvPossible() const = 0;
    glm::vec2 getPos();
    PieceColor getColor() const;
    void setPosition(glm::vec2 &pos);
    virtual void updateforme() = 0;


    PieceColor color;
    glm::vec2 pos;
    virtual std::vector<glm::vec3> getforme() const = 0;
    virtual std::vector<glm::vec2> getbuffer_image() const = 0;

};

#endif // PIECE_H
