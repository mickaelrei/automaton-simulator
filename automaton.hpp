#pragma once

#include <sstream>
#include <algorithm>
#include <functional>

/// @brief State handler, receives a value from the alphabet and returns the new state
/// @tparam A alphabet type
/// @tparam S state type
template<typename A, typename S>
using StateHandler = std::function<S(A)>;

template<typename A, typename S>
class Automaton {
public:
    /// @brief Constructor
    /// @param stateHandlers list of states with their handlers
    /// @param initialState initial state
    /// @param acceptingStates list of accepting states
    Automaton(
        const std::vector<std::pair<S, StateHandler<A, S>>> &stateHandlers,
        S initialState,
        const std::vector<S> &acceptingStates
    );

    /// @brief Simulates the automaton with a given word
    /// @param word list of alphabet values
    /// @return final state
    S simulate(const std::vector<A> &word);

    /// @brief Returns whether a state is an accepting state
    /// @param state state to test
    /// @return bool telling if state is accepting
    bool isAcceptingState(const S &state);

private:
    /// @brief State handlers map
    std::unordered_map<S, StateHandler<A, S>> handlersMap;

    /// @brief State to start simulation
    S initialState;

    /// @brief List of accepting states
    std::vector<S> acceptingStates;
};

template<typename A, typename S>
Automaton<A, S>::Automaton(
    const std::vector<std::pair<S, StateHandler<A, S>>> &stateHandlers,
    S initialState,
    const std::vector<S> &acceptingStates
) : initialState{initialState}, acceptingStates{acceptingStates} {
    for (auto &[state, handler] : stateHandlers) {
        handlersMap[state] = handler;
    }
}

template<typename A, typename S>
S Automaton<A, S>::simulate(const std::vector<A> &word) {
    S state = initialState;

    for (auto it = word.begin(); it != word.end(); ++it) {
        // Find handler for current state
        auto handler = handlersMap.find(state);
        if (handler == handlersMap.end()) {
            // Construct error message if state was not found
            std::stringstream err_msg{
                "ERROR [Automaton.simulate]: handler for state \"",
                std::ios_base::app | std::ios_base::out
            };
            err_msg << state;
            err_msg << "\" not found";
            throw std::runtime_error{err_msg.str()};
        }

        // Get new state from handler
        state = handler->second(*it);
    }

    return state;
}

template<typename A, typename S>
bool Automaton<A, S>::isAcceptingState(const S &state) {
    auto iter = std::find(acceptingStates.begin(), acceptingStates.end(), state);
    if (iter == acceptingStates.end()) {
        return false;
    }

    return true;
}