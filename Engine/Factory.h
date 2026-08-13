#pragma once

#include "Object.h"
#include "Singleton.h"
#include "EngineStrings.h"

#include <map>
#include <memory>

namespace ChiefEngine {
    class ICreator {
    public:
        virtual ~ICreator() = default;
        virtual std::unique_ptr<Object> Create() = 0;
    };

    template <typename T>
        requires std::derived_from<T, Object>
    class Creator : public ICreator {
    public:
        ~Creator() = default;
        std::unique_ptr<Object> Create() override { return std::make_unique<T>(); }
    };

    class Factory : public Singleton<Factory> {
    public:
        template <typename T>
            requires std::derived_from<T, Object>
        inline void Register(const std::string& name);

        template <typename T = class Object>
            requires std::derived_from<T, Object>
        inline std::unique_ptr<T> Create(const std::string& name);
    private:
        std::map<std::string, std::unique_ptr<ICreator>> m_registry;
    };

    template <typename T>
        requires std::derived_from<T, Object>
    inline void Factory::Register(const std::string& name) {
        std::string id = ToLower(name);
        if (m_registry.contains(id)) {
            std::cerr << name << " already registered in Object Registry\n";
            return;
        }
        m_registry[id] = std::make_unique<Creator<T>>();
    }

    template <typename T>
        requires std::derived_from<T, Object>
    inline std::unique_ptr<T> Factory::Create(const std::string& name) {
        std::string id = ToLower(name);

        if (!m_registry.contains(id)) {
            std::cerr << name << " not registered in Object Registry\n";
            return std::unique_ptr<T>();
        }

        auto object = m_registry[id]->Create();

        T* derived = dynamic_cast<T*>(object.get());
        
        if (derived) {
            object.release();
            return std::unique_ptr<T>(derived);
        } else {
            std::cerr << name << " and Object type mismatch\n";
            return std::unique_ptr<T>();
        }
    }
}