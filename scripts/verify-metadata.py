#!/usr/bin/env python3
"""
Repository Metadata Verification Script

Verifies that the console-snake-cpp repository has the recommended
topics and metadata configured for optimal discoverability.
"""

import requests
import sys
import json

# Expected repository configuration
EXPECTED_TOPICS = {
    "cpp", "cplusplus", "game", "console", "snake", 
    "cmake", "windows", "terminal", "gamedev", "no-dependencies"
}

EXPECTED_DESCRIPTION = "🐍 Classic Snake game in C++ that runs in Windows console - zero dependencies, just double-click to play!"

EXPECTED_FEATURES = {
    "has_issues": True,
    "has_wiki": True,
    "has_discussions": True,
    "has_projects": True
}

def check_repository_metadata(owner="Clubhouse1661", repo="console-snake-cpp"):
    """
    Check if the repository has the expected metadata configuration.
    
    Returns:
        dict: Status of each metadata component
    """
    url = f"https://api.github.com/repos/{owner}/{repo}"
    
    try:
        response = requests.get(url)
        response.raise_for_status()
        repo_data = response.json()
        
        # Check topics
        current_topics = set(repo_data.get("topics", []))
        missing_topics = EXPECTED_TOPICS - current_topics
        extra_topics = current_topics - EXPECTED_TOPICS
        
        # Check description
        current_description = repo_data.get("description", "")
        description_matches = current_description == EXPECTED_DESCRIPTION
        
        # Check features
        features_status = {}
        for feature, expected in EXPECTED_FEATURES.items():
            features_status[feature] = repo_data.get(feature, False) == expected
        
        return {
            "success": True,
            "topics": {
                "current": list(current_topics),
                "expected": list(EXPECTED_TOPICS),
                "missing": list(missing_topics),
                "extra": list(extra_topics),
                "matches": len(missing_topics) == 0 and len(extra_topics) == 0
            },
            "description": {
                "current": current_description,
                "expected": EXPECTED_DESCRIPTION,
                "matches": description_matches
            },
            "features": features_status,
            "all_features_enabled": all(features_status.values())
        }
        
    except requests.RequestException as e:
        return {
            "success": False,
            "error": f"Failed to fetch repository data: {e}",
            "suggestion": "Check internet connection or repository access permissions"
        }

def print_verification_report(status):
    """Print a formatted verification report."""
    print("🔍 Repository Metadata Verification Report")
    print("=" * 50)
    
    if not status["success"]:
        print(f"❌ Error: {status['error']}")
        print(f"💡 Suggestion: {status['suggestion']}")
        return
    
    # Topics verification
    print("\n🏷️ Repository Topics:")
    if status["topics"]["matches"]:
        print("✅ All expected topics are configured correctly")
        print(f"   Current topics: {', '.join(status['topics']['current'])}")
    else:
        print("❌ Topics configuration needs attention")
        if status["topics"]["missing"]:
            print(f"   Missing topics: {', '.join(status['topics']['missing'])}")
        if status["topics"]["extra"]:
            print(f"   Extra topics: {', '.join(status['topics']['extra'])}")
        print(f"   Expected: {', '.join(status['topics']['expected'])}")
    
    # Description verification
    print("\n📝 Repository Description:")
    if status["description"]["matches"]:
        print("✅ Repository description matches recommendation")
    else:
        print("❌ Repository description needs updating")
        print(f"   Current: {status['description']['current']}")
        print(f"   Expected: {status['description']['expected']}")
    
    # Features verification
    print("\n⚙️ Repository Features:")
    for feature, enabled in status["features"].items():
        feature_name = feature.replace("has_", "").title()
        status_icon = "✅" if enabled else "❌"
        print(f"   {status_icon} {feature_name}: {'Enabled' if enabled else 'Disabled'}")
    
    if status["all_features_enabled"]:
        print("✅ All recommended features are enabled")
    else:
        print("❌ Some recommended features need to be enabled")
    
    print("\n📈 Configuration Instructions:")
    print("   To apply these settings:")
    print("   1. Go to repository Settings > General")
    print("   2. Update Topics in the 'About' section")
    print("   3. Update Description in the 'About' section")
    print("   4. Enable Features in the 'Features' section")
    print("   5. See REPOSITORY_SETUP.md for detailed guidance")

def main():
    """Main verification function."""
    print("Verifying repository metadata configuration...")
    print("This may take a moment to fetch data from GitHub API...\n")
    
    status = check_repository_metadata()
    print_verification_report(status)
    
    # Exit with appropriate code
    if not status["success"]:
        sys.exit(1)
    
    all_correct = (
        status["topics"]["matches"] and 
        status["description"]["matches"] and 
        status["all_features_enabled"]
    )
    
    if all_correct:
        print("\n🎉 Repository metadata is fully configured!")
        sys.exit(0)
    else:
        print("\n⚠️  Repository metadata needs configuration updates")
        sys.exit(1)

if __name__ == "__main__":
    main()