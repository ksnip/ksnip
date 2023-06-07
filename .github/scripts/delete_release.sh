
GIT_COMMIT="${GITHUB_SHA}"
GIT_REPO_SLUG="${GITHUB_REPOSITORY}"

release_url="https://api.github.com/repos/${GIT_REPO_SLUG}/releases/tags/${RELEASE_TAG}"
echo "Getting the release ID..."
echo "release_url: ${release_url}"

release_infos=$(curl -XGET --header "Authorization: token ${GITHUB_TOKEN}" "${release_url}")
echo "release_infos: ${release_infos}"

release_id=$(echo "${release_infos}" | grep "\"id\":" | head -n 1 | tr -s " " | cut -f 3 -d" " | cut -f 1 -d ",")
echo "release ID: ${release_id}"

git fetch --tags origin
target_commit_sha=$(git rev-list -n 1 "${RELEASE_TAG}")
echo "target_commit_sha: ${target_commit_sha}"
echo "GIT_COMMIT: ${GIT_COMMIT}"

if [ "${GIT_COMMIT}" != "${target_commit_sha}" ] ; then

  echo "GIT_COMMIT != target_commit_sha, hence deleting release for tag ${RELEASE_TAG}..."

  if [ -n "${release_id}" ]; then
    delete_release_url="https://api.github.com/repos/${GIT_REPO_SLUG}/releases/${release_id}"
    echo "Delete the release..."
    echo "delete_url: ${delete_release_url}"
    curl -XDELETE \
        --header "Authorization: token ${GITHUB_TOKEN}" \
        "${delete_release_url}"
  fi

  if [ "${RELEASE_TAG}" == "continuous" ] ; then
    # if this is a continuous build tag, then delete the old tag
    # in preparation for the new release
    echo "Delete the tag..."
    delete_tag_url="https://api.github.com/repos/${GIT_REPO_SLUG}/git/refs/tags/${RELEASE_TAG}"
    echo "delete_url: ${delete_tag_url}"
    curl -XDELETE \
        --header "Authorization: token ${GITHUB_TOKEN}" \
        "${delete_tag_url}"
  fi

fi