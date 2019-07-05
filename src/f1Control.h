class f1Control : public paramControl {
public:
  float value;
  f1Control(ofShader* shader, string name, float min, float max, float def, string type);
  void setUniform();
  void (*drawPanel)();
  void drawSlider();
  void drawDragbox();
}
