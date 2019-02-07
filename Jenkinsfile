stage('Source') {
  node {
    sh 'setup_centreon_build.sh'
    dir('centreon-clib') {
      checkout scm
    }
    sh './centreon-build/jobs/clib/18.10/mon-clib-source.sh'
    source = readProperties file: 'source.properties'
    env.VERSION = "${source.VERSION}"
    env.RELEASE = "${source.RELEASE}"
    if (env.BRANCH_NAME == '18.10') {
      withSonarQubeEnv('SonarQube') {
        sh './centreon-build/jobs/clib/18.10/mon-clib-analysis.sh'
      }
    }
  }
}

try {
  stage('Package') {
    parallel 'centos7': {
      node {
        sh 'setup_centreon_build.sh'
        sh './centreon-build/jobs/clib/18.10/mon-clib-package.sh centos7'
      }
    }
    if ((currentBuild.result ?: 'SUCCESS') != 'SUCCESS') {
      error('Package stage failure.');
    }
  }
}
finally {
  buildStatus = currentBuild.result ?: 'SUCCESS';
  if ((buildStatus != 'SUCCESS') && (env.BRANCH_NAME == '18.10')) {
    slackSend channel: '#monitoring-metrology', message: "@channel Centreon Clib build ${env.BUILD_NUMBER} of branch ${env.BRANCH_NAME} was broken by ${source.COMMITTER}. Please fix it ASAP."
  }
}
