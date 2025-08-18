# 🛠️ Scripts Directory

This directory contains utility scripts for the Console Snake C++ project.

## 📁 Available Scripts

### 🔍 verify-metadata.py

Verifies that the repository has the recommended topics and metadata configured for optimal discoverability.

**Usage:**
```bash
python3 scripts/verify-metadata.py
```

### 🔍 verify-metadata.sh

Shell script wrapper for the Python verification tool with automatic dependency installation.

**Usage:**
```bash
bash scripts/verify-metadata.sh
```

**Features:**
- Automatically checks for Python 3 availability
- Installs required dependencies (`requests` library)
- Provides fallback instructions if automated verification fails
- Returns appropriate exit codes for CI/CD integration

**Features:**
- Checks if all recommended topics are configured
- Verifies repository description matches guidelines
- Validates repository features (Issues, Wiki, Discussions, Projects)
- Provides detailed configuration instructions

**Requirements:**
- Python 3.6+
- `requests` library (`pip install requests`)
- Internet connection to access GitHub API

**Example Output:**
```
🔍 Repository Metadata Verification Report
==================================================

🏷️ Repository Topics:
✅ All expected topics are configured correctly
   Current topics: cpp, cplusplus, game, console, snake, cmake, windows, terminal, gamedev, no-dependencies

📝 Repository Description:
✅ Repository description matches recommendation

⚙️ Repository Features:
   ✅ Issues: Enabled
   ✅ Wiki: Enabled
   ✅ Discussions: Enabled
   ✅ Projects: Enabled

🎉 Repository metadata is fully configured!
```

## 🎯 Purpose

These scripts help maintain the repository's metadata and ensure it follows best practices for:
- **Discoverability**: Proper topics and descriptions
- **Community**: Enabled features for collaboration
- **Professional appearance**: Consistent configuration

## 🔧 Adding New Scripts

When adding new scripts:
1. Make them executable (`chmod +x script.py`)
2. Include proper documentation headers
3. Update this README with script information
4. Follow the project's coding standards

---

*These tools help ensure the Console Snake C++ project maintains high-quality metadata for the GitHub community.*