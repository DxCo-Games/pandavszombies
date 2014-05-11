#ifndef ACTION_H_
#define ACTION_H_

namespace dxco {

class Action {
public:
	Action();
	virtual ~Action();

	virtual bool isFinished();
	virtual void run(float dt);
protected:
	bool finished;
};

} /* namespace dxco */
#endif /* ACTION_H_ */
