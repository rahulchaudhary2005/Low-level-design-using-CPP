
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
using namespace std;

// 1. Common abstraction for document elements
class DocumentElement {
public:
    virtual string render() const = 0;
    virtual ~DocumentElement() = default;
};

// 2. Text element
class TextElement : public DocumentElement {
private:
    string text;

public:
    explicit TextElement(const string& value) : text(value) {}

    string render() const override {
        return text;
    }
};

// 3. Image element
class ImageElement : public DocumentElement {
private:
    string imagePath;

public:
    explicit ImageElement(const string& path) : imagePath(path) {}

    string render() const override {
        return "[Image: " + imagePath + "]";
    }
};

// 4. Document owns its elements
class Document {
private:
    vector<unique_ptr<DocumentElement>> elements;

public:
    void addElement(unique_ptr<DocumentElement> element) {
        elements.push_back(move(element));
    }

    const vector<unique_ptr<DocumentElement>>& getElements() const {
        return elements;
    }
};

// 5. Responsible only for rendering the document
class DocumentRenderer {
public:
    string render(const Document& document) const {
        string result;

        for (const auto& element : document.getElements()) {
            result += element->render() + "\n";
        }

        return result;
    }
};

// 6. Responsible only for saving content
class DocumentSaver {
public:
    bool save(const string& content, const string& filename) const {
        ofstream file(filename);

        if (!file.is_open()) {
            return false;
        }

        file << content;
        file.close();

        return !file.fail();
    }
};

int main() {
    Document document;

    document.addElement(
        make_unique<TextElement>("Hello, world!")
    );

    document.addElement(
        make_unique<ImageElement>("picture.jpg")
    );

    document.addElement(
        make_unique<TextElement>("This is a document editor.")
    );

    DocumentRenderer renderer;
    string output = renderer.render(document);

    cout << output;

    DocumentSaver saver;

    if (saver.save(output, "document.txt")) {
        cout << "Document saved successfully.\n";
    } else {
        cout << "Failed to save document.\n";
    }

    return 0;
}
