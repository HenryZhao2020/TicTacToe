#ifndef TICTACTOE_SERIALIZABLE_H
#define TICTACTOE_SERIALIZABLE_H

#include <filesystem>
#include <iosfwd>
#include <utility>

/// Represents the result of a serialization operation.
struct SerializableError {
    /// Categories of errors that may occur.
    enum class Type {
        None = 0,           ///< No error.
        FileNotFoundError,  ///< File is not found.
        FileOpenError,      ///< File could not be opened.
        FileReadError,      ///< File could not be read.
        FileWriteError,     ///< File could not be written.
        FilesystemError,    ///< General filesystem failure.
        InvalidDataError    ///< File contents were invalid or corrupt.
    };

    Type type{Type::None};  ///< Error category.
    std::string message;    ///< Human-readable error message.

    SerializableError() = default;
    explicit SerializableError(const Type type, std::string message = {})
        : type{type}, message{std::move(message)} {}

    /// Returns true if there is no error.
    [[nodiscard]] bool good() const { return type == Type::None; }

    /// Evaluates to true if an error is present.
    explicit operator bool() const { return !good(); }
};

/// Base class for objects that can be saved to and loaded from a file.
/// Subclasses implement onSave() and onLoad() to define how state
///   is written and read.
/// Errors are reported via SerializableError.
class Serializable {
public:
    /// Binds this instance to a file path (inside dir by default).
    explicit Serializable(std::filesystem::path file,
                          std::filesystem::path dir = {"Saves"})
        : dir{std::move(dir)}, file{std::move(file)} {}
    virtual ~Serializable() = default;

    /// Saves the object to disk. Creates directories as needed.
    SerializableError save();

    /// Loads the object from disk.
    SerializableError load();

protected:
    /// Called by save(); subclasses must write their state to out.
    virtual SerializableError onSave(std::ostream& out) = 0;

    /// Called by load(); subclasses must restore their state from in.
    virtual SerializableError onLoad(std::istream& in) = 0;

private:
    std::filesystem::path dir;    ///< Target directory.
    std::filesystem::path file;   ///< Target file name.
};

#endif // TICTACTOE_SERIALIZABLE_H
