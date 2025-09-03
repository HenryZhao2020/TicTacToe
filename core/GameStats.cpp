#include "GameStats.h"

GameStats::GameStats() : Serializable{"GameStats.txt"} {}

void GameStats::update(const GameState result) {
    switch (result) {
    case GameState::XWon:
        ++xWins;
        break;
    case GameState::OWon:
        ++oWins;
        break;
    case GameState::Tie:
        ++ties;
        break;
    default:
        break;
    }
}

SerializableError GameStats::onSave(std::ostream &out) {
    out << xWins << '\n';
    out << oWins << '\n';
    out << ties << '\n';
    return {};
}

SerializableError GameStats::onLoad(std::istream &in){
    int xWinsRead{}, oWinsRead{}, tiesRead{};
    if (!(in >> xWinsRead >> oWinsRead >> tiesRead)) {
        return SerializableError{
            SerializableError::Type::FileReadError,
            "Cannot read GameStats"
        };
    }

    std::swap(xWins, xWinsRead);
    std::swap(oWins, oWinsRead);
    std::swap(ties,  tiesRead);
    return {};
}
