#include "Physics.h"

bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon) {
	size_t n = polygon.getVertexCount() - 1;
	size_t intersectionCount = 0;
	sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(),
		point.y);

	for (size_t i = 0; i < n; i++) {
		sf::Vector2f p1 = polygon[i].position;
		sf::Vector2f p2 = polygon[(i + 1) % n].position;

		if ((p1.y < point.y && p2.y >= point.y) ||
			(p2.y < point.y && p1.y >= point.y)) {
			float t = (point.y - p1.y) / (p2.y - p1.y);
			float intersectX = p1.x + t * (p2.x - p1.x);

			if (intersectX <= point.x && intersectX <= rayEnd.x) {
				intersectionCount++; //point is intersecting
			}
		}
	}

	return intersectionCount % 2 == 1;
}


bool physics::intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2) {  //error here
	size_t n1 = poly1.getVertexCount() - 1;
	size_t n2 = poly2.getVertexCount() - 1;

	for (size_t i = 0; i < n1; i++) {
		sf::Vector2f edge = poly1[i].position - poly1[(i + 1) % n1].position;
		sf::Vector2f normal(-edge.y, edge.x);

		//normalize the vector
		float length = sqrt(normal.x * normal.x + normal.y * normal.y);
		normal /= length;

		float min1 = std::numeric_limits<float>::max();
		float max1 = std::numeric_limits<float>::min();
		float min2 = std::numeric_limits<float>::max();
		float max2 = std::numeric_limits<float>::min();

		for (size_t j = 0; j < n1; j++) {
			float projection =
				poly1[j].position.x * normal.x + poly1[j].position.y * normal.y;
			min1 = std::min(min1, projection);
			max1 = std::max(max1, projection);
		}
		for (size_t j = 0; j < n1; j++) {
			float projection =
				poly2[j].position.x * normal.x + poly2[j].position.y * normal.y;
			min2 = std::min(min2, projection);
			max2 = std::max(max2, projection);
		}

		if (max1 < min2 || max2 < min1) {
			return false;
		}
	}

	return true;
}

sf::VertexArray physics::getTransformed(const sf::VertexArray& polygon,
	const sf::Transform& transform) {
	sf::VertexArray transformed = polygon;

	for (size_t i = 0; i < transformed.getVertexCount(); i++) {
		transformed[i].position = transform.transformPoint(transformed[i].position);
	}

	return transformed;
}
