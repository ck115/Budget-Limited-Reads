#include "accounting/logger.h"

namespace blr {

bool Logger::open(const std::string& logical_path, const std::string& replica_path) {
  logical_.open(logical_path);
  replica_.open(replica_path);
  return logical_.is_open() && replica_.is_open();
}

void Logger::log_logical(const LogicalRead&, bool) {
  // TODO
}

void Logger::log_replica(LogicalId, const ReplicaRead&, bool) {
  // TODO
}

}  // namespace blr
