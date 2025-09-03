#include "Serializable.h"

#include <fstream>
#include <sstream>
#include <system_error>

SerializableError Serializable::save() {
    // Create directory, if it does not exist.
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    if (ec) {
        return SerializableError{
            SerializableError::Type::FilesystemError,
            "Failed to create directory: " + dir.string() +
                ", " + ec.message() };
    }

    // Write data to a temporary string buffer.
    std::ostringstream buffer;
    if (auto err = onSave(buffer); err) return err;

    // Open the target file in write mode.
    const auto target = dir / file;
    std::ofstream out{target, std::ios::out | std::ios::trunc};
    if (!out) {
        return SerializableError{
            SerializableError::Type::FileOpenError,
            "Failed to open: " + target.string()
        };
    }

    // Checks for write error before file is closed.
    out << buffer.str();
    out.close();
    if (!out) {
        return SerializableError{
            SerializableError::Type::FileWriteError,
            "Failed to write: " + target.string()
        };
    }
    return {};
}

SerializableError Serializable::load() {
    const auto target = dir / file;

    // Existence check with error_code (no-throw)
    std::error_code ec;
    const bool exists = std::filesystem::exists(target, ec);  // noexcept
    if (ec) {
        return SerializableError{
            SerializableError::Type::FilesystemError,
            "std::filesystem::exists() failed for: " + target.string() +
                ", " + ec.message()
        };
    }
    if (!exists) {
        return SerializableError{
            SerializableError::Type::FileNotFoundError,
            "File not found: " + target.string()
        };
    }

    // Open the file in read mode.
    std::ifstream in{target, std::ios::in};
    if (!in) {
        return SerializableError{
            SerializableError::Type::FileOpenError,
            "Failed to open: " + target.string()
        };
    }

    if (auto err = onLoad(in); err) return err;

    // Check for lingering read error.
    if (in.bad() || (in.fail() && !in.eof())) {
        return SerializableError{
            SerializableError::Type::FileReadError,
            "Failed to read: " + target.string()
        };
    }
    return {};
}
