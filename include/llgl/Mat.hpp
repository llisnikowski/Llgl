#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace llgl
{
using namespace glm;

template <std::size_t W, std::size_t H>
using Mat = glm::mat<W, H, glm::f32, glm::defaultp>;

template <std::size_t W>
using Vec = glm::vec<W, float, glm::defaultp>;

} // namespace llgl