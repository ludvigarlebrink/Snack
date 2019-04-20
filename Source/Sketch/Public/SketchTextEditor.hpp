#pragma once

#include "BaseTypes.hpp"

#include <array>
#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace snack
{
class SKETCH_API SketchTextEditor
{
public:

    enum class PaletteIndex
    {
        Default,
        Keyword,
        Number,
        String,
        CharLiteral,
        Punctuation,
        Preprocessor,
        Identifier,
        KnownIdentifier,
        PreprocIdentifier,
        Comment,
        MultiLineComment,
        Background,
        Cursor,
        Selection,
        ErrorMarker,
        Breakpoint,
        LineNumber,
        CurrentLineFill,
        CurrentLineFillInactive,
        CurrentLineEdge,
        Max
    };

    enum class SelectionMode
    {
        Normal,
        Word,
        Line
    };

    struct Breakpoint
    {
        int mLine;
        bool mEnabled;
        std::string mCondition;

        Breakpoint()
            : mLine(-1)
            , mEnabled(false)
        {
        }
    };

    struct Coordinates
    {
        int mLine, mColumn;
        Coordinates() : mLine(0), mColumn(0) {}
        Coordinates(int aLine, int aColumn) : mLine(aLine), mColumn(aColumn)
        {
            assert(aLine >= 0);
            assert(aColumn >= 0);
        }
        static Coordinates Invalid() { static Coordinates invalid(-1, -1); return invalid; }

        bool operator ==(const Coordinates& o) const
        {
            return
                mLine == o.mLine &&
                mColumn == o.mColumn;
        }

        bool operator !=(const Coordinates& o) const
        {
            return
                mLine != o.mLine ||
                mColumn != o.mColumn;
        }

        bool operator <(const Coordinates& o) const
        {
            if (mLine != o.mLine)
                return mLine < o.mLine;
            return mColumn < o.mColumn;
        }

        bool operator >(const Coordinates& o) const
        {
            if (mLine != o.mLine)
                return mLine > o.mLine;
            return mColumn > o.mColumn;
        }

        bool operator <=(const Coordinates& o) const
        {
            if (mLine != o.mLine)
                return mLine < o.mLine;
            return mColumn <= o.mColumn;
        }

        bool operator >=(const Coordinates& o) const
        {
            if (mLine != o.mLine)
                return mLine > o.mLine;
            return mColumn >= o.mColumn;
        }
    };

    struct Identifier
    {
        Coordinates mLocation;
        std::string mDeclaration;
    };

    typedef std::string String;
    typedef std::unordered_map<std::string, Identifier> Identifiers;
    typedef std::unordered_set<std::string> Keywords;
    typedef std::map<int, std::string> ErrorMarkers;
    typedef std::unordered_set<int> Breakpoints;
    typedef std::array<uint32, (unsigned)PaletteIndex::Max> Palette;
    typedef char Char;

    struct Glyph
    {
        Char mChar;
        PaletteIndex mColorIndex = PaletteIndex::Default;
        bool mComment : 1;
        bool mMultiLineComment : 1;
        bool mPreprocessor : 1;

        Glyph(Char aChar, PaletteIndex aColorIndex) : mChar(aChar), mColorIndex(aColorIndex),
            mComment(false), mMultiLineComment(false), mPreprocessor(false) {}
    };

    typedef std::vector<Glyph> Line;
    typedef std::vector<Line> Lines;

    struct SKETCH_API LanguageDefinition
    {
        typedef std::pair<std::string, PaletteIndex> TokenRegexString;
        typedef std::vector<TokenRegexString> TokenRegexStrings;
        typedef bool(*TokenizeCallback)(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end, PaletteIndex & paletteIndex);

        std::string mName;
        Keywords mKeywords;
        Identifiers mIdentifiers;
        Identifiers mPreprocIdentifiers;
        std::string mCommentStart, mCommentEnd, mSingleLineComment;
        char mPreprocChar;
        bool mAutoIndentation;

        TokenizeCallback mTokenize;

        TokenRegexStrings mTokenRegexStrings;

        bool mCaseSensitive;

        LanguageDefinition()
            : mPreprocChar('#'), mAutoIndentation(true), mTokenize(nullptr), mCaseSensitive(true)
        {
        }

        static const LanguageDefinition& CPlusPlus();
        static const LanguageDefinition& HLSL();
        static const LanguageDefinition& GLSL();
        static const LanguageDefinition& C();
        static const LanguageDefinition& SQL();
        static const LanguageDefinition& AngelScript();
        static const LanguageDefinition& Lua();
    };

private:

    typedef std::vector<std::pair<std::regex, PaletteIndex>> RegexList;

    struct EditorState
    {
        Coordinates mSelectionStart;
        Coordinates mSelectionEnd;
        Coordinates mCursorPosition;
    };

    class UndoRecord
    {
    public:
        UndoRecord() {}
        ~UndoRecord() {}

        UndoRecord(
            const std::string& aAdded,
            const SketchTextEditor::Coordinates aAddedStart,
            const SketchTextEditor::Coordinates aAddedEnd,

            const std::string& aRemoved,
            const SketchTextEditor::Coordinates aRemovedStart,
            const SketchTextEditor::Coordinates aRemovedEnd,

            SketchTextEditor::EditorState& aBefore,
            SketchTextEditor::EditorState& aAfter);

        void Undo(SketchTextEditor* aEditor);
        void Redo(SketchTextEditor* aEditor);

        std::string mAdded;
        Coordinates mAddedStart;
        Coordinates mAddedEnd;

        std::string mRemoved;
        Coordinates mRemovedStart;
        Coordinates mRemovedEnd;

        EditorState mBefore;
        EditorState mAfter;
    };

    typedef std::vector<UndoRecord> UndoBuffer;

public:

    SketchTextEditor();

    virtual ~SketchTextEditor();

    void SetLanguageDefinition(const LanguageDefinition& aLanguageDef);

    const LanguageDefinition& GetLanguageDefinition() const { return mLanguageDefinition; }

    const Palette& GetPalette() const { return mPaletteBase; }

    void SetPalette(const Palette& aValue);

    void SetErrorMarkers(const ErrorMarkers& aMarkers) { mErrorMarkers = aMarkers; }

    void SetBreakpoints(const Breakpoints& aMarkers) { mBreakpoints = aMarkers; }

    void Render(const char* aTitle, const glm::vec2& aSize = glm::vec2(0.0f, 0.0f), bool aBorder = false);

    void SetText(const std::string& aText);

    void SetTextLines(const std::vector<std::string>& aLines);

    std::string GetText() const;

    std::vector<std::string> GetTextLines() const;

    std::string GetSelectedText() const;

    std::string GetCurrentLineText()const;

    int GetTotalLines() const { return (int)mLines.size(); }

    bool IsOverwrite() const { return mOverwrite; }

    void SetReadOnly(bool aValue);

    bool IsReadOnly() const { return mReadOnly; }

    bool IsTextChanged() const { return mTextChanged; }

    bool IsCursorPositionChanged() const { return mCursorPositionChanged; }

    Coordinates GetCursorPosition() const { return GetActualCursorCoordinates(); }

    void SetCursorPosition(const Coordinates& aPosition);

    void InsertText(const std::string& aValue);

    void InsertText(const char* aValue);

    void MoveUp(int aAmount = 1, bool aSelect = false);

    void MoveDown(int aAmount = 1, bool aSelect = false);

    void MoveLeft(int aAmount = 1, bool aSelect = false, bool aWordMode = false);

    void MoveRight(int aAmount = 1, bool aSelect = false, bool aWordMode = false);

    void MoveTop(bool aSelect = false);

    void MoveBottom(bool aSelect = false);

    void MoveHome(bool aSelect = false);

    void MoveEnd(bool aSelect = false);

    void SetSelectionStart(const Coordinates& aPosition);

    void SetSelectionEnd(const Coordinates& aPosition);

    void SetSelection(const Coordinates& aStart, const Coordinates& aEnd, SelectionMode aMode = SelectionMode::Normal);

    void SelectWordUnderCursor();

    void SelectAll();

    bool HasSelection() const;

    void Copy();

    void Cut();

    void Paste();

    void Delete();

    bool CanUndo() const;

    bool CanRedo() const;

    void Undo(int aSteps = 1);

    void Redo(int aSteps = 1);

    static const Palette& GetDarkPalette();

    static const Palette& GetLightPalette();

    static const Palette& GetRetroBluePalette();

private:

    void ProcessInputs();

    void Colorize(int aFromLine = 0, int aCount = -1);

    void ColorizeRange(int aFromLine = 0, int aToLine = 0);

    void ColorizeInternal();

    float TextDistanceToLineStart(const Coordinates& aFrom) const;

    void EnsureCursorVisible();

    int GetPageSize() const;

    int AppendBuffer(std::string& aBuffer, char chr, int aIndex);

    std::string GetText(const Coordinates& aStart, const Coordinates& aEnd) const;

    Coordinates GetActualCursorCoordinates() const;

    Coordinates SanitizeCoordinates(const Coordinates& aValue) const;

    void Advance(Coordinates& aCoordinates) const;

    void DeleteRange(const Coordinates& aStart, const Coordinates& aEnd);

    int InsertTextAt(Coordinates& aWhere, const char* aValue);

    void AddUndo(UndoRecord& aValue);

    Coordinates ScreenPosToCoordinates(const glm::vec2& aPosition) const;

    Coordinates FindWordStart(const Coordinates& aFrom) const;

    Coordinates FindWordEnd(const Coordinates& aFrom) const;

    bool IsOnWordBoundary(const Coordinates& aAt) const;

    void RemoveLine(int aStart, int aEnd);

    void RemoveLine(int aIndex);

    Line& InsertLine(int aIndex);

    void EnterCharacter(Char aChar, bool aShift);

    void BackSpace();

    void DeleteSelection();

    std::string GetWordUnderCursor() const;

    std::string GetWordAt(const Coordinates& aCoords) const;

    uint32 GetGlyphColor(const Glyph& aGlyph) const;

    void HandleKeyboardInputs();

    void HandleMouseInputs();

    void Render();

private:

    f32 mLineSpacing;
    Lines mLines;
    EditorState mState;
    UndoBuffer mUndoBuffer;
    int32 mUndoIndex;

    int32 mTabSize;
    bool mOverwrite;
    bool mReadOnly;
    bool mWithinRender;
    bool mScrollToCursor;
    bool mScrollToTop;
    bool mTextChanged;
    f32 mTextStart;
    int32  mLeftMargin;
    bool mCursorPositionChanged;
    int32 mColorRangeMin, mColorRangeMax;
    SelectionMode mSelectionMode;

    Palette mPaletteBase;
    Palette mPalette;
    LanguageDefinition mLanguageDefinition;
    RegexList mRegexList;

    bool mCheckComments;
    Breakpoints mBreakpoints;
    ErrorMarkers mErrorMarkers;
    glm::vec2 mCharAdvance;
    Coordinates mInteractiveStart, mInteractiveEnd;

    f32 mLastClick;
};
} // namespace snack
