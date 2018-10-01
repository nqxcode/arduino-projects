/****************************************************/

class Controller {
  public:
    Controller::Controller(void);
    void setAxes(unsigned int x, unsigned int y);
    Crawler::Direction getDirection();
    unsigned int getLeftSpeed();
    unsigned int getRightSpeed();

  private:
    Crawler::Direction direction;
    int leftSpeed;
    int rightSpeed;
};
