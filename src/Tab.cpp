#include "Tab.h"
#include "ESPDash.h"

/*
  Constructor
*/
Tab::Tab(ESPDash *dashboard, const char *name, const char *navbarName, const char *header):
  _dashboard(dashboard),
  _name(name),
  _navbarName(navbarName),
  _header(header)
{
  #if defined(ESP8266)
    _id = RANDOM_REG32;
  #elif defined(ESP32)
    _id = esp_random();
  #endif
  _dashboard->add(this);
}

// Add Card
Tab& Tab::add(Card *card) {
  return add(card, _cards);
}

// Remove Card
Tab& Tab::remove(Card *card) {
  return remove(card, _cards);
}

// Add Chart
Tab& Tab::add(Chart *chart) {
  return add(chart, _charts);
}

// Remove Chart
Tab& Tab::remove(Chart *chart) {
  return remove(chart, _charts);
}

Tab::JsonDocument Tab::toJSON() {
  JsonDocument doc(256);
  doc["id"] = _id;
  doc["name"] = _name;
  doc["navbarName"] = _navbarName;
  doc["header"] = _header;
  return std::move(doc);
}

template<class Object>
void Tab::mergeEntitiesToJSON(Vector<Object*>& container, JsonArray& jsonEntities, bool onlyChanged) {
  for(int i = 0; i < container.Size(); i++) {
    if (onlyChanged) {
      if (container[i]->isChanged())
        jsonEntities.add(container[i]->generateUpdate());
    }
    else
      jsonEntities.add(container[i]->generateUpdate());
  }
}

Tab::JsonDocument Tab::makeDocument(const String& command) {
  auto nrOfEntities = _cards.Size() + _charts.Size();
  JsonDocument doc(nrOfEntities * WIDGET_JSON_SIZE);

  doc["command"] = command;

  return std::move(doc);
}

Tab::JsonDocument Tab::generateLayout() {
  auto doc = makeDocument(String("updateLayout"));
  doc["version"] = "1";

  // Todo: WARNING duplicated code
  auto jsonCards = doc.createNestedArray("cards");
  for(int i = 0; i < _cards.Size(); i++)
    jsonCards.add(_cards[i]->generateLayout());

  auto jsonCharts = doc.createNestedArray("charts");
  for(int i = 0; i < _charts.Size(); i++)
    jsonCharts.add(_charts[i]->generateLayout());

  return std::move(doc);
}

Tab::JsonDocument Tab::generateUpdates(bool changeOnly) {
  auto doc = makeDocument(String("updates"));

  auto jsonCards = doc.createNestedArray("cards");
  mergeEntitiesToJSON(_cards, jsonCards, changeOnly);

  auto jsonCharts = doc.createNestedArray("charts");
  mergeEntitiesToJSON(_charts, jsonCharts, changeOnly);

  return std::move(doc);
}

void Tab::refreshLayout() {
  _dashboard->refreshLayout();
}

template<class Object>
Tab& Tab::add(Object *object, Vector<Object*> &container) {
  container.PushBack(object);
  refreshLayout();
  return *this;
}

template<class Object>
Tab& Tab::remove(Object *object, Vector<Object*> &container) {
  for(int i=0; i < container.Size(); i++){
    auto *p = container[i];
    if(p->getId() == object->getId()) {
      container.Erase(i);
      refreshLayout();
      return *this;
    }
  }
  return *this;
}

void Tab::resolveCardCallback(uint32_t id, int value) {
  auto findCard = [this, id]() -> Card* {
    for (int i = 0; i < _cards.Size(); ++i)
      if (_cards[i]->getId() == id)
        return _cards[i];
    return nullptr;
  };
  if (auto card = findCard())
    card->resolveCallback(value);
}

Tab::~Tab() {
  _dashboard->remove(this);
}