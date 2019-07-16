#include "./../headers/GlfwHeaders.h"
#include <cmath>
#include <iostream>

GlfwCollision::GlfwCollision()
{
}
GlfwCollision::GlfwCollision(GlfwGameControl *gameControl)
{
    this->gameControl = gameControl;
}

//TODO: Use separating axis theorem to do this
std::vector<GlfwSquare *> GlfwCollision::withSquare(GlfwSquare *sqObj)
{
    std::vector<GlfwSquare> *squaresAll = gameControl->getSquares();
    std::vector<GlfwSquare *> collidingSquares;

    bool collision = true; // Algorithm "assumes" for collision initially
    Coords coords1;        // = sqObj->getCoordinates();
    Coords coords2;

    GlfwSquare *sq1, *sq2;
    float theta, d1, d2, q1, q2;
    Vector2d P;
    for (int i = 0; i < squaresAll->size(); i++) //loop over squares
    {
        for (int n = 0; n < 2; n++) // loop over both squares to get all necessary projections
        {
            if (sqObj == &squaresAll->at(i))
                break;
            if (n == 0)
            {
                sq1 = sqObj;
                sq2 = &squaresAll->at(i);
            }
            else
            {
                sq1 = &squaresAll->at(i);
                sq2 = sqObj;
            }
            Coords coords1 = sq1->getCoordinates();
            Coords coords2 = sq2->getCoordinates();
            for (int j = 0; j < coords1.size() / 2; j++) // Loop over half of the points that make the square (can be applied to others this way)
            {
                /* First square */
                // Define P unit vector which is parallel
                // to one of the sides of the square
                // Square side angle
                theta = std::atan((coords1.at(j + 1).y - coords1.at(j).y) / (coords1.at(j + 1).x - coords1.at(j).x));
                // And finally P
                P.x = std::cos(theta);
                P.y = std::sin(theta);
                //Here d2 = d1+width OR d2 = d1+height
                d1 = coords1.at(j).dot(P);
                d2 = coords1.at(j + 1).dot(P);
                if (d2 < d1)
                {
                    d1 = d2;
                    d2 = coords1.at(j).dot(P);
                }
                /* Second square */
                // Calculate projections of each corner to P
                q1 = coords2.at(0).dot(P);
                q2 = coords2.at(0).dot(P);
                for (int k = 1; k < 4; k++)
                {
                    if (coords2.at(k).dot(P) < q1)
                        q1 = coords2.at(k).dot(P);
                    if (coords2.at(k).dot(P) > q2)
                        q2 = coords2.at(k).dot(P);
                }

                if (q1 >= d1 && q1 <= d2 || q2 >= d1 && q2 <= d2 ||
                    d1 >= q1 && d1 <= q2 || d2 >= q1 && d2 <= q2)
                {
                    // Collision happens in this projection
                    // do something?
                }
                else
                {
                    j = -1;
                    n = -1;
                }

                if (j == -1)
                    break;
            }
            if (n == -1)
            {
                break;
            }
            if (n == 1)
            {
                collidingSquares.emplace_back(sq1);
            }
        }
    }

    return collidingSquares;
}