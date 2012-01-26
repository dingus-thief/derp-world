#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State();
        virtual void handle() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

    private:
};

#endif // STATE_H
