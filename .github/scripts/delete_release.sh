
GIT_COMMIT="${GITHUB_SHA}"
GIT_REPO_SLUG="${GITHUB_REPOSITORY}"

release_url="https://api.github.com/repos/${GIT_REPO_SLUG}/releases/tags/${RELEASE_TAG}"
echo "Getting the release ID..."
echo "release_url: ${release_url}"

release_infos=$(curl -XGET --header "Authorization: token ${GITHUB_TOKEN}" "${release_url}")
echo "release_infos: ${release_infos}"
release_id=$(echo "${release_infos}" | grep "\"id\":" | head -n 1 | tr -s " " | cut -f 3 -d" " | cut -f 1 -d ",")
echo "release ID: ${release_id}"
target_commit_sha=$(echo "${release_infos}" | grep '"target_commitish":' | head -n 1 | cut -d '"' -f 4 | cut -d '{' -f 1)
echo "target_commit_sha: ${target_commit_sha}"

git fetch --tags origin

git tag

existingReleaseCommit=$(git rev-list -n 1 "${RELEASE_TAG}")

echo "GITHUB_REF: ${GITHUB_REF}"
echo "GIT_COMMIT: ${GIT_COMMIT}"
echo "target_commit_sha: ${target_commit_sha}"
echo "Commit of tag: ${existingReleaseCommit}"
echo "GIT_COMMIT != target_commit_sha, hence deleting release for tag ${RELEASE_TAG}..."

if [ "$GIT_COMMIT" != "${existingReleaseCommit}" ] ; then

  if [ ! -z "${release_id}" ]; then
    delete_url="https://api.github.com/repos/${GIT_REPO_SLUG}/releases/${release_id}"
    echo "Delete the release..."
    echo "delete_url: ${delete_url}"
#    curl -XDELETE \
#        --header "Authorization: token ${GITHUB_TOKEN}" \
#        "${delete_url}"
  fi

fi # if [ "$GIT_COMMIT" != "$tag_sha" ]