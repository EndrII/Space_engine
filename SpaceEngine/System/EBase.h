#ifndef EBASE_H
#define EBASE_H


class EBase
{
public:
    virtual EBase() = delete;

    virtual void render() = delete; //perechislenie dannh klassa obj=vsrobjecti v pole zreniya
    virtual void update(int, int) = delete;

    virtual ~EBase() = delete;

};

#endif // EBASE_H
