#ifndef __TAB_H
#define __TAB_H

#include <WString.h>

#include "vector.h"
#include "Widget.h"
#include "Card.h"
#include "Chart.h"

// Forward Declaration
class ESPDash;
namespace ArduinoJson {
  class ArrayRef;
}

// Tab Class
class Tab {
  private:
    ESPDash *_dashboard;

    uint32_t _id;
    String _name;
    String _navbarName;
    String _header;
    Vector<Card*> _cards;
    Vector<Chart*> _charts;

    // Helper functions
    using JsonDocument = Widget::JsonDocument;
    JsonDocument makeDocument(const String& command);
    template<class Object>
    void mergeEntitiesToJSON(Vector<Object*>& container, ArduinoJson::ArrayRef& jsonEntities, bool changeOnly);

    // Generate tab info as JSON document
    JsonDocument toJSON();

    // Generate layout json
    JsonDocument generateLayout();

    // Generate cards/charts update json
    JsonDocument generateUpdates(bool changeOnly = true);

    // This method is called when a card/chart is added or removed
    void refreshLayout();

    // Add/remove either Card or Chart
    template<class Object>
    Tab& add(Object *object, Vector<Object*> &container);

    template<class Object>
    Tab& remove(Object *object, Vector<Object*> &container);

    void resolveCardCallback(uint32_t id, int value);

  public:
    Tab(ESPDash *dashboard, const char* name, const char* navbarName, const char* header);

    // Add Card
    Tab& add(Card *card);
    // Remove Card
    Tab& remove(Card *card);

    // Add Chart
    Tab& add(Chart *chart);
    // Remove Chart
    Tab& remove(Chart *chart);

    uint32_t getId() const {
      return _id;
    }

    const String& getName() const {
      return _name;
    }

    ~Tab();

    friend class ESPDash;
};

#endif
