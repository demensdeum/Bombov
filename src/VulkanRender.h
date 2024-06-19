#include "Render.h"

namespace DemensDeum::Bombov {

class VulkanRender: public Render {

void setScene(std::shared_ptr<Scene> scene) override;
void render() override;

};

}