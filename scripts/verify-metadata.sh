#!/bin/bash
# Repository Metadata Verification Runner
# 
# This script helps run the Python verification tool with fallback options
# if Python dependencies are not available.

echo "🔍 Repository Metadata Verification"
echo "=================================="
echo

# Check if Python 3 is available
if ! command -v python3 &> /dev/null; then
    echo "❌ Python 3 is not available"
    echo "📝 Please install Python 3 to use the automated verification"
    echo "🔧 Alternative: Check manually using METADATA_CHECKLIST.md"
    exit 1
fi

# Check if requests library is available
if ! python3 -c "import requests" &> /dev/null; then
    echo "📦 Installing required Python dependencies..."
    if command -v pip3 &> /dev/null; then
        pip3 install requests
    elif command -v pip &> /dev/null; then
        pip install requests
    else
        echo "❌ pip is not available"
        echo "📝 Please install the 'requests' library manually:"
        echo "   pip install requests"
        echo "🔧 Alternative: Check manually using METADATA_CHECKLIST.md"
        exit 1
    fi
fi

# Run the verification script
echo "🚀 Running metadata verification..."
echo
python3 scripts/verify-metadata.py

exit_code=$?

echo
if [ $exit_code -eq 0 ]; then
    echo "✅ Verification completed successfully!"
else
    echo "⚠️  Verification found issues to address"
    echo "📋 See METADATA_CHECKLIST.md for manual configuration steps"
fi

exit $exit_code