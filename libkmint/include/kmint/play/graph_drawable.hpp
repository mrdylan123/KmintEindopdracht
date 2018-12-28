#ifndef KMINT_PLAY_GRAPH_RENDERABLE_HPP
#define KMINT_PLAY_GRAPH_RENDERABLE_HPP

#include "kmint/graph/basic_graph.hpp"
#include "kmint/graphics/color.hpp"
#include "kmint/graphics/image.hpp"
#include "kmint/math/size.hpp"
#include "kmint/ui/drawable.hpp"
#include "kmint/ui/window.hpp"

namespace kmint::play {

class actor;

template <typename Graph> class graph_drawable : public ui::drawable {
public:
  graph_drawable(Graph const &g)
      : ui::drawable{}, graph_{&g}, weight_range_{weight_range(g)} {}
  void draw(ui::frame &f) const override {
    // draw edges
    f.render_color(edge_color);
    for (auto const &node : *graph_) {
      for (auto const &edge : node) {
        // TODO: Add weights as soon as frame supports it
        f.draw_line(edge.from().location(),
                    edge.to().location() /*, edge.weight()*/);
      }
    }
    // draw nodes
    // f.render_color(node_color);
    for (auto const &node : *graph_) {
      auto color =
          graphics::color::from_hsv(120 * (1.f - normalize(node[0].weight())),
                                    node.tagged() ? 0.0f : 1.f, 1.f);
      f.draw_rectangle(node.location(), node_size, color);
    }
  }

private:
  static constexpr math::size node_size = {5.0f, 5.0f};
  static constexpr graphics::color node_color = {255, 0, 0};
  static constexpr graphics::color tagged_node_color = {0, 255, 255};
  static constexpr graphics::color edge_color = {255, 255, 255};
  float normalize(float weight) const noexcept {
    auto[min, max] = weight_range_;
    return (weight - min) / (max - min);
  }
  Graph const *graph_;
  std::pair<float, float> weight_range_;
};
} // namespace kmint::play

#endif /* KMINT_PLAY_GRAPH_RENDERABLE_HPP */
