/****************************************************/

class Controller {
  public:
    Controller::Controller(void);
    void setAxes(int x, int y);
    Crawler::Direction getDirection();
    int getLeftSpeed();
    int getRightSpeed();

  private:
    Crawler::Direction direction;
    int leftSpeed;
    int rightSpeed;
};
