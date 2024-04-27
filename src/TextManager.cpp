#include "TextManager.hpp"

TextManager::TextManager(const wxString &filePath) : filePath(filePath), currentPosition(0), chunkSize(1024 * 1024) {
    file.Open(filePath);
}

wxString TextManager::LoadInitialChunk() {
    return LoadChunk(0);
}

wxString TextManager::LoadNextChunk() {
    long newPosition = currentPosition + chunkSize;
    return LoadChunk(newPosition);
}

wxString TextManager::LoadPreviousChunk() {
    long newPosition = currentPosition - chunkSize;
    return LoadChunk(newPosition);
}

wxString TextManager::LoadChunk(long position) {
    if (!file.IsOpened()) {
        wxLogError("Cannot open file '%s'.", filePath);
        return wxEmptyString;
    }

    file.Seek(position, wxFromStart);
    size_t toRead = chunkSize;
    wxChar* fileBuffer = new wxChar[toRead + 1];
    size_t bytesRead = file.Read(fileBuffer, toRead);
    fileBuffer[bytesRead] = '\0';

    wxString buffer(fileBuffer);
    delete[] fileBuffer;

    currentPosition += bytesRead;
    return buffer;
}
